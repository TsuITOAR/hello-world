/*
 * @lc app=leetcode.cn id=115 lang=rust
 *
 * [115] 不同的子序列
 */
pub struct Solution;
// @lc code=start
impl Solution {
    pub fn num_distinct(s: String, t: String) -> i32 {
		use std::collections::HashMap;
		let mut letter_index_map=HashMap::new();
		for (index,letter) in t.char_indices(){
			letter_index_map.entry(letter).or_insert(Vec::new()).push(index);
		}
		let mut queue=vec![0;t.bytes().len()+1];
		*queue.first_mut().unwrap()=1;
		for ch in s.chars(){
			//println!("{:?}",queue);
			match letter_index_map.get(&ch){
				None=>continue,
				Some(indexes_mapped)=>{
					for i in indexes_mapped.iter().rev(){
						queue[i+1]+=queue[*i];
					}
				}
			}
		}
		return *queue.last().unwrap();
    }
}
// @lc code=end

