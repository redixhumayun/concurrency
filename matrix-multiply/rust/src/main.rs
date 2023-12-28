use rand::Rng;

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
    let rows = 2;
    let cols = 2;
    let a: Vec<Vec<i32>> = (0..rows)
        .map(|_| {
            return (0..cols)
                .map(|_| rand::thread_rng().gen_range(1..100))
                .collect();
        })
        .collect();

    let b: Vec<Vec<i32>> = (0..rows)
        .map(|_| {
            return (0..cols)
                .map(|_| rand::thread_rng().gen_range(1..100))
                .collect();
        })
        .collect();

    println!("{:?}", a);
    println!("{:?}", b);

    let c = matrix_multiply(&a, &b);
    println!("{:?}", c);
}
