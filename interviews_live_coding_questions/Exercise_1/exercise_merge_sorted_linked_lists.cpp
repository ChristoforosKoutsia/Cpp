/*
 * For your reference:
 *
 * SinglyLinkedListNode {
 *     int data;
 *     SinglyLinkedListNode* next;
 * };
 *
 */
SinglyLinkedListNode* mergeLists(SinglyLinkedListNode* head1, SinglyLinkedListNode* head2) {

SinglyLinkedListNode dummy = SinglyLinkedListNode(0); // initialize the dummy value here
SinglyLinkedListNode* node = &dummy  ;

while (head1 && head2) {
    
    if (head1->data <= head2->data)
    {
        node->next = head1;
        head1 = head1->next;
        node = node ->next;
    }
    
    else{
        node->next = head2;
        head2 = head2->next;
        node = node ->next;
    }

}

node->next = head1 ? head1 : head2;

return (dummy.next) ;

}