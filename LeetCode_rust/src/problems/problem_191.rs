/*
 * @lc app=leetcode.cn id=191 lang=rust
 *
 * [191] 位1的个数
 */
pub struct Solution;
// @lc code=start
impl Solution {
    pub fn hammingWeight(n: u32) -> i32 {
        let mut n = n;
        let mut ret = 0;
        while n != 0 {
            ret += 1;
            n = n & (n - 1);
        }
        ret
    }
}
// @lc code=end
