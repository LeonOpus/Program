fn main() {
    // 所有权基础
    let s1 = String::from("hello");
    let s2 = s1; // s1的所有权转移给s2
    // println!("{}", s1); // 这行会报错，因为s1已经不再有效
    println!("{}", s2);
    
    // 克隆
    let s3 = s2.clone();
    println!("s2 = {}, s3 = {}", s2, s3);
    
    // 函数与所有权
    let s = String::from("ownership");
    takes_ownership(s);
    // println!("{}", s); // 报错，s的所有权已转移
    
    let x = 5;
    makes_copy(x);
    println!("{}", x); // 可以，因为i32实现了Copy trait
}

fn takes_ownership(some_string: String) {
    println!("{}", some_string);
}

fn makes_copy(some_integer: i32) {
    println!("{}", some_integer);
}