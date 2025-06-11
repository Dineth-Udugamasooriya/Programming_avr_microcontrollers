public class LinkedList<T>{
    class ListNode<T>{
        public T data;
        public ListNode<T> next;

        public ListNode(T data){
            this.data = data;
            this.next = null;
        }
    }
    ListNode<T> head;

    public LinkedList(){
        this.head = null;
    }

    public void add(T data){
        ListNode<T> temp = new ListNode<T>(data);
        temp.next = head;
        head = temp;
    }

    public T delete(){
        if(head!= null){
            T tmp = head.data;
            head = head.next;
            return tmp;

        }
        return null;
    }
}



