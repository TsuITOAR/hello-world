/*
 * @lc app=leetcode.cn id=850 lang=rust
 *
 * [850] 矩形面积 II
 */
pub struct Solution;
// @lc code=start
impl Solution {
    pub fn rectangle_area(rectangles: Vec<Vec<i32>>) -> i32 {
        const M: i64 = 1000000007;
        use std::collections::BTreeMap;
        use std::collections::BTreeSet;
        let mut x_pos_y_set_map = BTreeMap::new();
        fn adjust_set(y: (i32, i32), y_set: &mut BTreeSet<(i32, i32)>) -> i32 {
            let (start, end) = y;
            let mut ret = end - start;
            let mut new_start = start;
            let mut new_end = end;
            let set_filter = |(y1, y2): &&(i32, i32)| -> bool {
                !match (y1 >= &start, y1 < &end, y2 >= &start, y2 < &end) {
                    //return true if stay in set
                    /*
                    _ _ 0 _
                    _ 0 _ _
                    0 _ _ 0
                    1 _ _ 1
                    */
                    //y1 y2 start end 0 1 0 1
                    (_, _, false, _) => true,
                    //start end y1 y2 1 0 1 0
                    (_, false, _, _) => true,
                    //start y1 y2 end 1 1 1 1
                    (true, _, _, true) => {
                        ret -= y2 - y1;
                        false
                    }
                    //y1 start end y2 0 1 1 0
                    (false, _, _, false) => {
                        new_start = *y1;
                        new_end = *y2;
                        ret = 0;
                        false
                    }
                    //y1 start y2 end 0 1 1 1
                    (false, true, true, true) => {
                        ret -= y2 - start;
                        new_start = *y1;
                        false
                    }
                    //start y1 end y2 1 1 1 0
                    (true, true, true, false) => {
                        ret -= end - y1;
                        new_end = *y2;
                        false
                    }
                }
            };
            let elements_to_remove: Vec<_> = y_set
                .iter()
                .take_while(|y| y.0 < end)
                .filter(set_filter)
                .copied()
                .collect();
            for element in elements_to_remove {
                y_set.remove(&element);
            }
            y_set.insert((new_start, new_end));
            return ret;
        }
        fn add_rect(
            rectangle: Vec<i32>,
            x_pos_y_set_map: &mut BTreeMap<i32, BTreeSet<(i32, i32)>>,
        ) -> i64 {
            let (x1, x2) = (rectangle[0], rectangle[2]);
            let y = (rectangle[1], rectangle[3]);
            let mut pos = -1;
            let mut last_pos = -1;
            let mut it = x_pos_y_set_map.keys();
            loop {
                match it.next() {
                    None => break,
                    Some(&key) => {
                        if key >= x1 {
                            pos = key;
                            break;
                        }
                        last_pos = key;
                    }
                }
            }
            let new_set = BTreeSet::new();
            let mut last_y_set = match last_pos {
                -1 => &new_set,
                _ => &x_pos_y_set_map[&last_pos],
            };
            let mut current_pos = x1;
            let mut ret = 0;
            let mut nodes_to_insert = Vec::new();
            //match pos
            match pos {
                -1 => (),
                pos => {
                    let mut key = Some(&pos);
                    loop {
                        match key {
                            None => break,
                            Some(&next_pos) => {
                                if next_pos >= x2 {
                                    break;
                                }
                                nodes_to_insert.push((current_pos, last_y_set.clone()));
                                ret += (next_pos - current_pos) as i64 * {
                                    let temp =
                                        adjust_set(y, &mut nodes_to_insert.last_mut().unwrap().1);
                                    if temp == 0 {
                                        nodes_to_insert.pop();
                                    }
                                    temp
                                }
                                    as i64;
                                current_pos = next_pos;
                                last_y_set = &x_pos_y_set_map[&next_pos];
                            }
                        }
                        key = it.next();
                    }
                }
            }
            nodes_to_insert.push((current_pos, last_y_set.clone()));
            ret += (x2 - current_pos) as i64 * {
                let temp = adjust_set(y, &mut nodes_to_insert.last_mut().unwrap().1);
                if temp == 0 {
                    nodes_to_insert.pop();
                }
                temp
            } as i64;
            let last_y_set = last_y_set.clone();
            x_pos_y_set_map.entry(x2).or_insert(last_y_set);
            for node in nodes_to_insert {
                x_pos_y_set_map.insert(node.0, node.1);
            }
            //println!("{:?}", x_pos_y_set_map);
            return ret;
        }
        (rectangles.into_iter().fold(0, |acc, rectangle| {
            acc + add_rect(rectangle, &mut x_pos_y_set_map)
        }) % M) as i32
    }
}
// @lc code=end
