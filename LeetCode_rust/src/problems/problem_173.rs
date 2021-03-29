/*
 * @lc app=leetcode.cn id=173 lang=rust
 *
 * [173] 二叉搜索树迭代器
 */

#[derive(Debug, PartialEq, Eq)]
pub struct TreeNode {
    pub val: i32,
    pub left: Option<Rc<RefCell<TreeNode>>>,
    pub right: Option<Rc<RefCell<TreeNode>>>,
}

impl TreeNode {
    #[inline]
    pub fn new(val: i32) -> Self {
        TreeNode {
            val,
            left: None,
            right: None,
        }
    }
}
// @lc code=start
use std::{cell::RefCell, rc::Rc};
#[derive(Debug)]
pub struct BSTIterator {
    path: Vec<Rc<RefCell<TreeNode>>>,
    log: Vec<bool>,
}

/**
 * `&self` means the method takes an immutable reference.
 * If you need a mutable reference, change it to `&mut self` instead.
 */
impl BSTIterator {
    fn new(root: Option<Rc<RefCell<TreeNode>>>) -> Self {
        let mut log = Vec::new();
        let mut path = Vec::new();
        let mut node = root;
        while let Some(n) = node {
            path.push(n.clone());
            log.push(false);
            node = n.borrow().left.clone();
        }
        BSTIterator { path, log }
    }

    fn next(&mut self) -> i32 {
        println!("{:#?}", self.path);
        println!("{:#?}", self.path);
        let mut node = self.path.last().unwrap().borrow().right.clone();
        match node.clone().unwrap().borrow().right {
            None => {
                while let Some(true) = self.log.pop() {
                    self.path.pop();
                }
                *self.log.last_mut().unwrap() = true;
                while let Some(n) = node {
                    self.path.push(n.clone());
                    self.log.push(false);
                    node = n.borrow().left.clone();
                }
                return node.unwrap().borrow().val;
            }
            Some(right_node) => {
                self.path.push(node.clone().unwrap());
                self.log.push(false);

				return node.unwrap().borrow().val;
            }
        }
    }

    fn has_next(&self) -> bool {
        for state in self.log.iter() {
            if *state == false {
                return true;
            }
        }
        return false;
    }
}

// @lc code=end
