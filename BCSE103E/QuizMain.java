import java.util.Scanner;
import java.util.Arrays;
import java.util.Random;

class QuizMain{
        public static void main(String args[]){
                final int number_of_questions_to_ask = 5;
                int score=0;
                String data[][] = {
                    {"The capital city of Tamil Nadu State", "Chennai", "Madurai", "Salem", "Trichy", "a"},
                    {"The currency of India", "Dollar", "Frank", "Rupee", "Yen", "c"},
                    {"The currency of USA", "Dollar", "Frank", "Rupee", "Yen", "a"},
                    {"The currency of China", "Dollar", "Frank", "Rupee", "Yuan", "d"},
                    {"The capital city of Maharashtra", "Delhi", "Mumbai", "Chennai", "Calcutta", "b"},
                    {"The capital city of West Bengal", "Delhi", "Mumbai", "Chennai", "Calcutta", "d"},
                    {"The capital city of Karnataka", "Delhi", "Mumbai", "Bangalore","Calcutta","c"},
                    {"The capital city of Kerala","Trivandrum","Mumbai","Bangalore","Calcutta","a"},
                    {"The currency of Singapore","Dollar","Sdollar","Rupee","Yen","b"},
                    {"The currency of Japan","Dollar","Frank","Rupee","Yen","d"}
                };
                String alphabet[] = {"A", "B", "C", "D"};
                Scanner sc = new Scanner(System.in);
                int pending_number_of_questions_to_ask = number_of_questions_to_ask;
                for(int i=data.length-1; i>0; --i){
                    if(pending_number_of_questions_to_ask<=0){
                        System.out.println("You have answered all the questions");
                        break;
                    }
                    if(Math.random() < 0.5){
                        continue;
                    }
                    System.out.println("0. Exit\n1. Next Question\n");
                    String choice = sc.next();
                    if(choice.equals("0")){
                        break;
                    }
                    System.out.println("Question " + (i+1) + ": " + data[i][0]);
                    for(int j=0; j<4; ++j){
                        System.out.println(alphabet[j] + ". " + data[i][j+1]);
                    }
                    System.out.print("Your answer: ");
                    char answer = Character.toLowerCase(sc.next().charAt(0));
                    //sc.nextLine();
                    if(data[i][5].charAt(0) == answer){
                        ++score;
                    }
                    --pending_number_of_questions_to_ask;
                }
            System.out.println("Your score: " + score);
        }
}