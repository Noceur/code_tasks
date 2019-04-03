class Solution:
    def mergeTwoLists(self, l1: ListNode, l2: ListNode) -> ListNode:
        m = []
        if l1:
            while l1.next:
                m.append(l1.val)
                l1 = l1.next
            m.append(l1.val)
        if l2:
            while l2.next:
                m.append(l2.val)
                l2 = l2.next
            m.append(l2.val)
        m.sort()
        return m
