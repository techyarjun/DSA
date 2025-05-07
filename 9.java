import java.util.*;

public class SortingMenu {

    // Max-Heap sort (heap sort) implementation
    public static void heapSort(int[] arr) {
        int n = arr.length;
 // Build the max heap
        for (int i = n / 2 - 1; i >= 0; i--) {
            heapify(arr, n, i);
        }

        // Extract elements one by one from the heap
        for (int i = n - 1; i >= 0; i--) {
            // Move the current root to the end
            int temp = arr[0];
            arr[0] = arr[i];
            arr[i] = temp;

            // Call heapify on the reduced heap
            heapify(arr, i, 0);
        }
    }

    // To maintain the max heap property
    private static void heapify(int[] arr, int n, int i) {
        int largest = i;  // Initialize largest as root
        int left = 2 * i + 1; // left child
        int right = 2 * i + 2; // right child

        // If left child is larger than root
        if (left < n && arr[left] > arr[largest]) {
            largest = left;
        }

        // If right child is larger than the largest so far
        if (right < n && arr[right] > arr[largest]) {
            largest = right;
        }

        // If largest is not root
        if (largest != i) {
            int swap = arr[i];
            arr[i] = arr[largest];
            arr[largest] = swap;

            // Recursively heapify the affected sub-tree
            heapify(arr, n, largest);
        }
    }

    // Function to display the heap structure as a simple list
    public static void displayTree(int[] arr) {
        System.out.println("Heap Structure (Array view): ");
        System.out.println(Arrays.toString(arr));
    }

    // Function to display the array
    public static void displayArray(int[] arr) {
        System.out.println("Sorted Array in Ascending Order: " + Arrays.toString(arr));
    }

    // Function to take user input for array elements
    private static int[] getInputArray(int capacity, Scanner scanner) {
        int[] arr = new int[capacity];
        int count = 0;

        while (count < capacity) {
            System.out.print("Enter element " + (count + 1) + ": ");
            if (scanner.hasNextInt()) {
                arr[count] = scanner.nextInt();
                count++;
            } else {
                System.out.println("Invalid input. Please enter an integer.");
                scanner.next(); // Clear the invalid input
            }
        }
        return arr;
    }

    // Main method to handle menu-driven program
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        while (true) {
            System.out.println("\nMenu:");
            System.out.println("1. Enter the total number of elements");
            System.out.println("2. Exit");
            System.out.print("Enter your choice: ");
            int choice = scanner.nextInt();
            scanner.nextLine();  // Consume newline

            if (choice == 2) {
                System.out.println("Exiting program.");
                break;
            }

            if (choice == 1) {
                System.out.print("Enter the total number of elements: ");
                int capacity = scanner.nextInt();
                scanner.nextLine(); // Consume newline

                // Get user input for array elements
                int[] arr = getInputArray(capacity, scanner);

                // Display the tree (heap structure before sorting)
                System.out.println("\nHeap Structure before Sorting:");
                displayTree(arr);

                // Apply Heap Sort
                heapSort(arr);

                // Display the sorted array
                displayArray(arr);
                break;
            } else {
                System.out.println("Invalid choice. Please try again.");
            }
        }

        scanner.close();
    }
}

