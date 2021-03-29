use core::panic;

/*
 * @lc app=leetcode.cn id=54 lang=rust
 *
 * [54] 螺旋矩阵
 */
pub struct Solution;
// @lc code=start
impl Solution {
    pub fn spiral_order(matrix: Vec<Vec<i32>>) -> Vec<i32> {
        let mut border = (
            0_isize,
            0_isize,
            matrix.first().unwrap().len() as isize,
            matrix.len() as isize,
        );
        fn is_in_border(border: (isize, isize, isize, isize), point: (isize, isize)) -> bool {
            return point.1 >= border.0
                && point.1 < border.2
                && point.0 >= border.1
                && point.0 < border.3;
        }
        let mut move_direction = [(0_isize, 1_isize), (1, 0), (0, -1), (-1, 0)]
            .iter()
            .cycle();
        let mut ret = Vec::new();
        let mut point = (0_isize, 0_isize);
        ret.push(matrix[point.0 as usize][point.1 as usize]);
        while ret.len() < matrix.len() * matrix.first().unwrap().len() {
            let step = move_direction.next().unwrap();
            let mut next_point = (point.0 + step.0, point.1 + step.1);
            while is_in_border(border, next_point) {
                point = next_point;
                ret.push(matrix[point.0 as usize][point.1 as usize]);
                next_point = (next_point.0 + step.0, next_point.1 + step.1);
            }
            match step {
                (0, 1) => border.1 += 1,
                (1, 0) => border.2 -= 1,
                (0, -1) => border.3 -= 1,
                (-1, 0) => border.0 += 1,
                _ => panic!("Unknown move direction"),
            }
        }
        return ret;
    }
}
// @lc code=end
