#include "../../../include/singly_linked_list.h"
#include "../../../include/utils.h"
#include <iostream>
#include <vector>

using namespace std;

bool isPalindrome(ListNode *head) {
  vector<int> nums;
  while (head != nullptr) {
    nums.push_back(head->val);
    head = head->next;
  }
  for (int l = 0, r = nums.size() - 1; l < r; l++, r--)
    if (nums[l] != nums[r])
      return false;
  return true;
}

int main() {
  printTitle("Palindrome Linked List");
  vector<int> nums = {1, 2, 2, 1};
  ListNode *head = arrayToLinkedList(nums);
  printLinkedList(head);
  string solution = isPalindrome(head) ? "True" : "False";
  cout << "Solution: " << solution << endl;
  return 0;
}
