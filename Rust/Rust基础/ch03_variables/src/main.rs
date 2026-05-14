fn main() {
    // 变量绑定
    let x = 5;
    println!("x = {}", x);
    
    // 可变变量
    let mut y = 10;
    println!("y = {}", y);
    y = 20;
    println!("修改后的y = {}", y);
    
    // 变量遮蔽
    let z = 5;
    let z = z + 1;
    let z = z * 2;
    println!("z = {}", z);
    
    // 常量
    const MAX_POINTS: u32 = 100_000;
    println!("最大分数: {}", MAX_POINTS);
}