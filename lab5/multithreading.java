// multithreading using pthreads in java
public class multithreading{
    public static void main(String[] args){
        Thread t1 = new Thread(new Runnable(){ // Runnable is an interface
            //Thread class has a constructor which takes an object of Runnable interface
            //Thread is a class which is used to create a thread
            // we are creating an object of Runnable interface
            // and passing it to the Thread class
            // we are overriding the run method of Runnable interface
            //run method is the entry point of the thread
            //runnable interface means what? it means that the class which implements the runnable interface
            public void run(){
                for(int i=0;i<5;i++){
                    System.out.println("Hi");
                    try{ // why is try catch used here? because sleep method throws an exception so we need to handle it

                        Thread.sleep(1000);//sleep method is used to pause the thread for a specific amount of time
                        //what's the need of using sleep method? because we want to see the output of both threads
                        //if we don't use sleep method then the output of both threads will be mixed
                        //because both threads are running simultaneously
                        //so we are using sleep method to pause the thread for a specific amount of time
                    }catch(Exception e){} // why is catch block empty? because we are not doing anything with the exception

                }
            }
        });

        Thread t2 = new Thread(new Runnable(){
            public void run(){
                for(int i=0;i<5;i++){
                    System.out.println("Hello");
                    try{Thread.sleep(1000);}catch(Exception e){}
                }
            }
        });

        t1.start();
        //t1.start() is used to start the thread
        try{Thread.sleep(10);}catch(Exception e){}
        t2.start();
        //t2.start() is used to start the thread

        try{
            t1.join(); // what is the use of join method? join method is used to wait for the thread to die
            //if we don't use join method then the main thread will die before the t1 and t2 threads
            //and we will not be able to see the output of t1 and t2 threads
            //so we are using join method to wait for the t1 and t2 threads to die
            //what is main thread? main thread is the thread which is created by the JVM
            t2.join();

        }catch(Exception e){} // why is catch block empty? because we are not doing anything with the exception
        System.out.println("Bye");

                                    
        }


    }
    
