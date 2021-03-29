/*
 * @lc app=leetcode.cn id=5 lang=rust
 *
 * [5] 最长回文子串
 */
pub struct Solution{}
// @lc code=start
impl Solution {
    pub fn longest_palindrome(s: String) -> String {
        if s.len() <= 1 {
            return s;
        }
        let s: Vec<_> = s.chars().enumerate().collect();
        let mut ret = &s[0..1];
        for index in 0..s.len() {
            let (left, right) = s[..].split_at(index);
            let start_index_left = match left.last() {
                None => continue,
                Some(&(index, _)) => index,
            };
            for i in 0..=1 {
                let start_index_right = index + i;
                if start_index_right >= s.len() {
                    break;
                }
                let right = &right[i..];
                let mut iter = left.iter().rev().zip(right.iter());
                println!("{:?}", left);
                println!("{:?}", right);
                let temp = loop {
                    match iter.next() {
                        Some((&(index_left, char_left), &(index_right, char_right)))
                            if char_left != char_right =>
                        {
                            break &s[index_left + 1..index_right];
                        }
                        Some(_) => continue,
                        None => {
                            break {
                                match left.len() < right.len() {
                                    true => &s[0..start_index_right + left.len()],
                                    false => &s[start_index_left + 1 - right.len()..],
                                }
                            }
                        }
                    }
                };
                println! {"{:?}",temp};
                if temp.len() > ret.len() {
                    ret = temp
                }
            }
        }
        return ret.into_iter().map(|x| x.1).collect();
    }
}
// @lc code=end
