use rand::Rng;
use std::thread;
use std::time::Instant;

fn merge_sort_parallel(arr: &mut [i32]) {
    let mid = arr.len() / 2;
    if mid == 0 {
        return;
    }
}

fn merge_sort(arr: &mut [i32]) {
    let mid = arr.len() / 2;
    if mid == 0 {
        return;
    }

    merge_sort(&mut arr[0..mid]);
    merge_sort(&mut arr[mid..]);

    let mut res = arr.to_vec();
    merge(&arr[0..mid], &arr[mid..], &mut res[..]);
    arr.copy_from_slice(&res[..]);
}

fn merge(left: &[i32], right: &[i32], ret: &mut [i32]) {
    let mut left_index = 0;
    let mut right_index = 0;
    let mut ret_index = 0;
    while left_index < left.len() && right_index < right.len() {
        if left[left_index] <= right[right_index] {
            ret[ret_index] = left[left_index];
            left_index += 1;
        } else {
            ret[ret_index] = right[right_index];
            right_index += 1;
        }
        ret_index += 1;
    }

    if left_index < left.len() {
        ret[ret_index..].copy_from_slice(&left[left_index..]);
    } else if right_index < right.len() {
        ret[ret_index..].copy_from_slice(&right[right_index..]);
    }
}

fn main() {
    let mut array: Vec<i32> = (0..10)
        .map(|_| rand::thread_rng().gen_range(1..100))
        .collect();
    let start = Instant::now();
    merge_sort(&mut array);
    let duration = start.elapsed();
    println!("Time elapsed is: {:?}", duration);
    println!("THe sorted array: {:?}", array);

    // println!("{:?}", array);
}
