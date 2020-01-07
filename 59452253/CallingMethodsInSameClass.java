
public class CallingMethodsInSameClass
{
     public static void main(String[] args) {
        printOne();
        printOne();
        printTwo();
        {
        	int i=0;
        }
      }

    public static void printOne() {
       System.out.println("Hello World");
     }

     public static void printTwo() {
       printOne();
       printOne();
    } 
}
