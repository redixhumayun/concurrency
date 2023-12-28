use rayon::prelude::*;
use std::time::Instant;

use rand::Rng;
use std::thread;

const TILE_SIZE: usize = 500;

fn multiply_matrix_tiles(
    a: &Vec<Vec<i32>>,
    b: &Vec<Vec<i32>>,
    m: usize,
    n: usize,
    p: usize,
    i_start: usize,
    j_start: usize,
) -> Vec<Vec<i32>> {
    let mut output_matrix = vec![vec![0; TILE_SIZE]; TILE_SIZE];
    for i in 0..TILE_SIZE {
        for j in 0..TILE_SIZE {
            if i_start + i < m && j_start + j < p {
                for k in 0..n {
                    output_matrix[i][j] += a[i_start + i][k] * b[k][j_start + j];
                }
            }
        }
    }
    output_matrix
}

fn matrix_multiply_with_tiles(a: &Vec<Vec<i32>>, b: &Vec<Vec<i32>>) -> Vec<Vec<i32>> {
    let m = a.len();
    let n = b.len();
    let p = b[0].len();

    let mut threads = vec![];

    for i in (0..m).step_by(TILE_SIZE) {
        for j in (0..p).step_by(TILE_SIZE) {
            let a_clone = a.to_vec();
            let b_clone = b.to_vec();

            threads.push(thread::spawn(move || {
                multiply_matrix_tiles(&a_clone, &b_clone, m, n, p, i, j)
            }));
        }
    }

    let mut result = vec![vec![0; p]; m];

    // Inside matrix_multiply_tiled_parallel, after joining threads:
    for (idx, thread) in threads.into_iter().enumerate() {
        let partial_result = thread.join().unwrap();
        let tile_row = idx / ((m + TILE_SIZE - 1) / TILE_SIZE);
        let tile_col = idx % ((p + TILE_SIZE - 1) / TILE_SIZE);

        for (i, row) in partial_result.into_iter().enumerate() {
            for (j, val) in row.into_iter().enumerate() {
                if tile_row * TILE_SIZE + i < m && tile_col * TILE_SIZE + j < p {
                    result[tile_row * TILE_SIZE + i][tile_col * TILE_SIZE + j] = val;
                }
            }
        }
    }
    result
}

fn matrix_multiply_with_parallelism(a: &Vec<Vec<i32>>, b: &Vec<Vec<i32>>) -> Vec<Vec<i32>> {
    let m = a.len();
    let n = b.len();
    let p = b[0].len();

    let c: Vec<Vec<i32>> = (0..m)
        .into_par_iter()
        .map(|i| {
            let mut c_row = Vec::with_capacity(p);
            for j in 0..p {
                let mut sum = 0;
                for k in 0..n {
                    sum += a[i][k] * b[k][j];
                }
                c_row.push(sum);
            }
            c_row
        })
        .collect();
    c
}

fn transpose(matrix: &Vec<Vec<i32>>) -> Vec<Vec<i32>> {
    let rows = matrix.len();
    let cols = matrix[0].len();

    let mut matrix_transpose = vec![vec![0; rows]; cols];

    for row in 0..rows {
        for col in 0..cols {
            matrix_transpose[col][row] = matrix[row][col];
        }
    }

    return matrix_transpose;
}

fn matrix_multiply_with_transpose(a: &Vec<Vec<i32>>, b: &Vec<Vec<i32>>) -> Vec<Vec<i32>> {
    let m = a.len();
    let n = a[0].len();
    let p = b.len();

    let mut c = Vec::with_capacity(m); //  initialising the buffer for just m rows

    for i in 0..m {
        let mut c_row = Vec::with_capacity(p);
        for j in 0..p {
            let mut sum = 0;
            for k in 0..n {
                sum += a[i][k] * b[j][k];
            }
            c_row.push(sum);
        }
        c.push(c_row);
    }
    c
}

fn matrix_multiply_with_no_buffer(a: &Vec<Vec<i32>>, b: &Vec<Vec<i32>>) -> Vec<Vec<i32>> {
    let m = a.len();
    let n = b.len();
    let p = b[0].len();

    let mut c = Vec::with_capacity(m); //  initialising the buffer for just m rows

    for i in 0..m {
        let mut c_row = Vec::with_capacity(p);
        for j in 0..p {
            let mut sum = 0;
            for k in 0..n {
                sum += a[i][k] * b[k][j];
            }
            c_row.push(sum);
        }
        c.push(c_row);
    }
    c
}

fn matrix_multiply(a: &Vec<Vec<i32>>, b: &Vec<Vec<i32>>) -> Vec<Vec<i32>> {
    let m = a.len();
    let n = b.len();
    let p = b[0].len();

    let mut c = vec![vec![0; p]; m];

    for i in 0..m {
        for j in 0..p {
            for k in 0..n {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }

    return c;
}

fn main() {
    let rows_a = 1000;
    let cols_a = 1000;

    let rows_b = 1000;
    let cols_b = 1000;

    let a: Vec<Vec<i32>> = (0..rows_a)
        .map(|_| {
            return (0..cols_a)
                .map(|_| rand::thread_rng().gen_range(1..100))
                .collect();
        })
        .collect();

    let b: Vec<Vec<i32>> = (0..rows_b)
        .map(|_| {
            return (0..cols_b)
                .map(|_| rand::thread_rng().gen_range(1..100))
                .collect();
        })
        .collect();

    let start = Instant::now();
    let c = matrix_multiply(&a, &b);
    let duration = start.elapsed();
    println!("Time duration for sequential: {:?}", duration);

    let start = Instant::now();
    let c_unbuffered = matrix_multiply_with_no_buffer(&a, &b);
    let duration = start.elapsed();
    println!("Time duration for no buffer: {:?}", duration);
    assert_eq!(c, c_unbuffered);

    let b_transpose = transpose(&b);
    let start = Instant::now();
    let c_tranpose = matrix_multiply_with_transpose(&a, &b_transpose);
    let duration = start.elapsed();
    println!("Time duration for transpose: {:?}", duration);
    assert_eq!(c, c_tranpose);

    let start = Instant::now();
    let c_parallel = matrix_multiply_with_parallelism(&a, &b);
    let duration = start.elapsed();
    println!("Time duration for parallel: {:?}", duration);
    assert_eq!(c, c_parallel);

    let start = Instant::now();
    let c_tiled = matrix_multiply_with_tiles(&a, &b);
    let duration = start.elapsed();
    println!("Time duration for tiled: {:?}", duration);
    assert_eq!(c, c_tiled);
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn multiply_matrix_tiles_test() {
        let a: Vec<Vec<i32>> = (0..TILE_SIZE)
            .map(|_| {
                return (0..TILE_SIZE)
                    .map(|_| rand::thread_rng().gen_range(1..100))
                    .collect();
            })
            .collect();

        let b: Vec<Vec<i32>> = (0..TILE_SIZE)
            .map(|_| {
                return (0..TILE_SIZE)
                    .map(|_| rand::thread_rng().gen_range(1..100))
                    .collect();
            })
            .collect();

        let m = a.len();
        let n = b.len();
        let p = b[0].len();

        let output_matrix = multiply_matrix_tiles(&a, &b, m, n, p, 0, 0);
        println!("{:?}", output_matrix);
        assert_eq!(output_matrix.len(), TILE_SIZE);
        assert_eq!(output_matrix, matrix_multiply(&a, &b));
    }

    #[test]
    fn multiply_matrix_tiles_threads_test() {
        let a: Vec<Vec<i32>> = vec![vec![1, 2, 3], vec![4, 5, 6]];
        let b: Vec<Vec<i32>> = vec![vec![7, 8], vec![9, 10], vec![11, 12]];
        let output_matrix = matrix_multiply_with_tiles(&a, &b);
        println!("{:?}", output_matrix);
        assert_eq!(output_matrix, vec![vec![58, 64], vec![139, 154]]);
    }
}
