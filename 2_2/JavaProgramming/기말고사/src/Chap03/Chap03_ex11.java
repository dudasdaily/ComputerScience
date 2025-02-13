package Chap03;

class Chap03_ex11 {
    public static void main(String[] args) {
        int[][] arr = new int[4][];

        arr[0] = new int[3];
        arr[1] = new int[2];
        arr[2] = new int[3];
        arr[3] = new int[2];

        for(int i = 0; i < 4; i++) {
            for(int j = 0; j < arr[i].length; j++) {
                arr[i][j] = (i+1) * 10 + j;

                System.out.printf("%d ", arr[i][j]);
            }
            System.out.println();
        }
    }
}