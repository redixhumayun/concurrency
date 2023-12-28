use std::time::Instant;

use rand::Rng;

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
}
