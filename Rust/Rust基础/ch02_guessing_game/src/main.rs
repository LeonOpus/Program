use rand::Rng;
use std::io;

fn main() {
    println!("猜数字游戏!");

    let secret_number = rand::thread_rng().gen_range(1, 101);

    loop {
        println!("请输入你的猜测 (1-100):");

        let mut guess = String::new();
        io::stdin().read_line(&mut guess).expect("读取失败");

        let guess: u32 = match guess.trim().parse() {
            Ok(num) => num,
            Err(_) => {
                println!("请输入有效的数字!");
                continue;
            }
        };

        match guess.cmp(&secret_number) {
            std::cmp::Ordering::Less => println!("太小了!"),
            std::cmp::Ordering::Greater => println!("太大了!"),
            std::cmp::Ordering::Equal => {
                println!("恭喜你，猜对了!");
                break;
            }
        }
    }
}
