/*
 * @lc app=leetcode.cn id=456 lang=rust
 *
 * [456] 132模式
 */
pub struct Solution;
// @lc code=start
impl Solution {
    pub fn find132pattern(nums: Vec<i32>) -> bool {
        let mut min = *nums.first().unwrap();
        let mut range = (min, min);
        for i in nums {
            if i > range.0 && i < range.1 {
                return true;
            } else if i < min {
                min = i;
            } else {
                if i > range.1 {
                    range.1 = i;
                }
                if min < range.0 {
                    range.0 = i;
                }
            }
        }
        return false;
    }
}
// @lc code=end
