package com.company;
import java.util.*;
import java.util.concurrent.CountDownLatch;

public class SortThread extends Thread {
    List<Integer> sublist;
    CountDownLatch count;
    SortThread(List<Integer> sublist, CountDownLatch count){
        super();
        this.sublist = sublist;
        this.count = count;
        start();
    }
    public void run(){
        try{
            Main.gnomeSort(sublist);
            count.countDown();
        } catch(Exception e){
            System.out.print("Thread RIP");
            e.printStackTrace();
        }
    }
}

