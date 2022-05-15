package com.company;

import org.jetbrains.annotations.NotNull;

import java.io.IOException;
import java.math.BigInteger;
import java.util.Scanner;
import java.util.*;
import java.util.concurrent.CountDownLatch;

public class Main {
    public static void mergeArrayElements(ArrayList<Integer> arrayToSort, int indexStart, int indexMiddle, int indexEnd) {
        ArrayList<Integer> tempArray = new ArrayList<>();
        int getLeftIndex = indexStart;
        int getRightIndex = indexMiddle + 1;
        while (getLeftIndex <= indexMiddle && getRightIndex <= indexEnd) {
            if (arrayToSort.get(getLeftIndex) <= arrayToSort.get(getRightIndex)) {
                tempArray.add(arrayToSort.get(getLeftIndex));
                getLeftIndex++;
            } else {
                tempArray.add(arrayToSort.get(getRightIndex));
                getRightIndex++;
            }
        }
        while (getLeftIndex <= indexMiddle) {
            tempArray.add(arrayToSort.get(getLeftIndex));
            getLeftIndex++;
        }
        while (getRightIndex <= indexEnd) {
            tempArray.add(arrayToSort.get(getRightIndex));
            getRightIndex++;
        }

        for (int i = 0; i < tempArray.size(); indexStart++) {
            arrayToSort.set(indexStart, tempArray.get(i++));
        }
    }

    public static void mergeSort(ArrayList<Integer> array,int indexStart, int indexEnd) {

        if (indexStart < indexEnd && (indexEnd - indexStart) >= 1) {
            int middleElement = (indexEnd + indexStart) / 2;

            mergeSort(array,indexStart, middleElement);
            mergeSort(array,middleElement + 1, indexEnd);

            mergeArrayElements(array,indexStart, middleElement, indexEnd);
        }
    }
    public static void gnomeSort(List<Integer> sublist){
        int i = 1;
        int j = 2;
        while (i < sublist.size()) {
            if (sublist.get(i) > sublist.get(i - 1)) {
                i = j;
                j++;
            }
            else {
                Collections.swap(sublist, i, i - 1);
                i--;
                if (i == 0) {
                    i = j;
                    j++;
                }
            }
        }
    }
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        Random rand = new Random();
        int size = 0,numThreads = 0;
        try {
        System.out.println("Array size: ");
        size = Integer.parseInt(scanner.nextLine());
        System.out.println("Enter am of threads:");
        numThreads = Integer.parseInt(scanner.nextLine());
        } catch(Exception e){
            System.out.println("Issue with input");
            e.printStackTrace();
        }
        ArrayList<Integer> arlist = new ArrayList<Integer>();
        for (int i = 0; i < size; i++) arlist.add(rand.nextInt(20));
        /*System.out.println("Unsorted array: ");
        for (Integer i : arlist)
            System.out.println(i);
         */
        CountDownLatch count = new CountDownLatch(numThreads);
        int subSize = size;
        long startTime = System.currentTimeMillis();
        long endTime = startTime;
        if (numThreads > 0) {
            subSize = size / numThreads;
            for (int i = 0; i < numThreads; i++) {
                int start = i * subSize;
                int end = (i + 1) * subSize;
                if (end > arlist.size() - 1) end = arlist.size();
                new SortThread(arlist.subList(start, end), count);
            }
            try {
                count.await();
                mergeSort(arlist, 0, arlist.size() - 1);
                endTime = System.currentTimeMillis();

            } catch (InterruptedException e) {
                System.out.println("Something went wrong");
                e.printStackTrace();
            }
            System.out.println("Time spent:" + (endTime - startTime));
        /*for (Integer i : arlist)
            System.out.println(i);
            */
        } else{
            gnomeSort(arlist);
            endTime = System.currentTimeMillis();
            System.out.println("Time spent:" + (endTime - startTime));
        }
        scanner.close();
    }
}


      //  Scanner scanner = new Scanner(System.in);
        //System.out.println("Enter an integer: ");
        //Long input = Long.parseLong(scanner.nextLine());
        //BigInteger bigInteger = BigInteger.valueOf(input);
        //int array[] = Main.intToArray(bigInteger);
       // Main.threeDot(array);



