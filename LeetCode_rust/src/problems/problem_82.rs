/*
 * @lc app=leetcode.cn id=82 lang=rust
 *
 * [82] 删除排序链表中的重复元素 II
 */
pub struct Solution;
#[derive(PartialEq, Eq, Clone, Debug)]
pub struct ListNode {
  pub val: i32,
  pub next: Option<Box<ListNode>>
}

impl ListNode {
  #[inline]
  fn new(val: i32) -> Self {
    ListNode {
      next: None,
      val
    }
  }
}
// @lc code=start
// Definition for singly-linked list.

impl Solution {
    pub fn delete_duplicates(head: Option<Box<ListNode>>) -> Option<Box<ListNode>> {
		let ret=head.clone();
		let mut head=head;
		let mut head=&mut head;
		while let Some(node)=head{
			let mut next_node=node;
			let mut temp=node;
			while let Some(ref mut next_temp)=temp.next{
				if temp.val!=next_temp.val{
					next_node=temp;
					break;
				}
				temp=next_temp;
			}
			*head=next_node.next.take();
		}
		return ret;
    }
}
// @lc code=end

