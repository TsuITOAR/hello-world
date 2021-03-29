/*
 * @lc app=leetcode.cn id=59 lang=rust
 *
 * [59] 螺旋矩阵 II
 */
pub struct Solution;
// @lc code=start
impl Solution {
    pub fn generate_matrix(n: i32) -> Vec<Vec<i32>> {
        let mut border = (0_isize, 0_isize, n as isize, n as isize);
        fn is_in_border(border: (isize, isize, isize, isize), point: (isize, isize)) -> bool {
            return point.1 >= border.0
                && point.1 < border.2
                && point.0 >= border.1
                && point.0 < border.3;
        }
        let mut move_direction = [(0_isize, 1_isize), (1, 0), (0, -1), (-1, 0)]
            .iter()
            .cycle();
        let mut matrix = vec![vec![0; n as usize]; n as usize];
        let mut point = (0_isize, 0_isize);
        let mut i = 1;
        matrix[point.0 as usize][point.1 as usize] = i;
        i += 1;
        while i <= n * n {
            let step = move_direction.next().unwrap();
            let mut next_point = (point.0 + step.0, point.1 + step.1);
            while is_in_border(border, next_point) {
                point = next_point;
                matrix[point.0 as usize][point.1 as usize] = i;
                i += 1;
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
        return matrix;
    }
}
// @lc code=end
