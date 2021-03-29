use std::option;

/*
 * @lc app=leetcode.cn id=705 lang=rust
 *
 * [705] 设计哈希集合
 */

// @lc code=start
pub struct MyHashSet<T: PartialOrd> {
    set: Option<Box<Set<T>>>,
}

struct Set<T: PartialOrd> {
    left_node: Option<Box<Self>>,
    right_node: Option<Box<Self>>,
    val: T,
}

impl<T: PartialOrd> Set<T> {
    fn insert(&mut self, val: T) {
        if val < self.val {
            self.left_node = Some(Box::new(Set::<T> {
                left_node: self.left_node,
                right_node: None,
                val,
            }));
        } else if val > self.val {
            self.right_node = Some(Box::new(Set::<T> {
                left_node: None,
                right_node: self.right_node,
                val,
            }));
        }
    }
    fn reorganize(&mut self) {
        let left = self.left_node;
        let right = self.right_node;
    }
}
/**
 * `&self` means the method takes an immutable reference.
 * If you need a mutable reference, change it to `&mut self` instead.
 */
impl<T: PartialOrd> MyHashSet<T> {
    /** Initialize your data structure here. */

    fn new() -> Self {
        MyHashSet { set: Option::None }
    }

    fn add(&self, key: T) {
        match self.set {
            None => {
                self.set = Some(Box::new(Set {
                    left_node: None,
                    right_node: None,
                    val: key,
                }))
            }
            Some(node) => loop {
                match *node {
                    Set::<T> {
                        left_node: Some(left),
                        right_node: Some(right),
                        val,
                    } => {
                        if left.val > key {
                            node = left;
                        } else if right.val < key {
                            node = right;
                        } else {
                            node.insert(key);
                            return;
                        }
                    }
                    Set::<T> {
                        left_node: Some(left),
                        ..
                    } => {
                        if left.val > key {
                            node = left;
                        } else {
                            node.insert(key);
                            return;
                        }
                    }
                    Set::<T> {
                        right_node: Some(right),
                        ..
                    } => {
                        if right.val < key {
                            node = right;
                        } else {
                            node.insert(key);
                            return;
                        }
                    }
                    _ => {
                        node.insert(key);
                        return;
                    }
                }
            },
        }
    }

    fn remove(&self, key: i32) {}

    /** Returns true if this set contains the specified element */
    fn contains(&self, key: i32) -> bool {}
}

/* *
 * Your MyHashSet object will be instantiated and called as such:
 * let obj = MyHashSet::new();
 * obj.add(key);
 * obj.remove(key);
 * let ret_3: bool = obj.contains(key);
 */
// @lc code=end
