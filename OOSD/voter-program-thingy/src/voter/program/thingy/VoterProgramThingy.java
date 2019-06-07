/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package voter.program.thingy;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import static java.lang.System.exit;
import java.text.DecimalFormat;
import java.util.ArrayList;
import java.util.Random;
import java.util.Scanner;
import java.util.concurrent.TimeUnit;



/**
 *
 * @author Demon From Hell
 */
public class VoterProgramThingy {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
        System.out.println("[+] Loading voter data...");
        String voterData[][] = loadFiles();
        System.out.println("[+] " + Integer.toString(voterData.length) + " candidates have loaded...");
        System.out.println("[+] Parsing data...");
        System.out.println("");
         
        for (int i = 0; i != voterData.length; i++){
            System.out.println("[" + Integer.toString(i) + "] - Name              : " + voterData[i][0]);
            System.out.println("      Age               : " + voterData[i][1]);
            System.out.println("      Party             : " + voterData[i][2]);
            System.out.println("      Scandal Count     : " + voterData[i][3]);
            System.out.println("      PR Disasters      : " + voterData[i][4]);
            System.out.println("      Promises to town  : " + voterData[i][5]);
            System.out.println("");
        }
        startVoting(voterData);
    }
    
    static void startVoting(String candidateData[][]){
        
        // UPDATE : Thanks to icebear's love to democracy there will
        // an additional part to this function which is loading the voter
        // verifcation data...
        String voterData[] = getVoterList();
        
        
    // so this function will have two parts
    //
    // the first part will generate a 8 bit hex string and
    // show it to the operator. Once the operator has noted the
    // string they can press enter and the program will clear the screen.
    //
    // once the voteing time has been completed the operator can key in the
    // 8 bit code and the system will exit
    //
        String closingVote = getRandomHexString(8);
        Scanner VariableInput = new Scanner(System.in);
        boolean continueVoting = true;
        boolean voteid_lock = false;
        String voterId;
        System.out.println("[+] To finish up a voting process you have to key in this 8-Bit hex : " + closingVote);
        System.out.println("[+] Please press enter to clear the screen and start the voting process");
        String operator_continue = VariableInput.nextLine();
        
        // now we are going to burn the body and dissolve the teeth in acid... I mean
        // make an array
        double votes[] = new double[candidateData.length];
        
        clearScreen();
        
        
        while (continueVoting){
            clearScreen();
            // alright... lets start voting... so before can start
            // voting we'll have to import tha voter verification from the disk.
            // But... we already did that... hmm....
            // ah yes, first we'll hav to prompt the user to enter their voter data
            // in this case they'll be prompted to enter an ID
            System.out.println("[!] Please enter your voter ID : ");
            voteid_lock = true;
            
            while (voteid_lock){ // lock the user in a while loop
                voterId = VariableInput.nextLine(); // prompt the user to enter their voter id
                System.out.println("[+] Checking username...");

                
                for (int i = 0; i < voterData.length; i++){ // loop through all the voter id
                    if (voterId.equals(voterData[i])){ // check if the voter id is the currently selected voterData[] element
                        voteid_lock = false; // if so set the voteid_lock to false
                        voterData[i] = "COMPLETE"; // change his index value in the voter list array...
                    }
                }
                
                if (voteid_lock){ // if the code reaches this part of the code and
                    // the voteid_lock is still true that means that the system cannot find the username
                    System.out.println("[!] Your token is invalid or already used...");
                    System.out.println("[+] Please re-enter your voter ID : ");
                }
            }
            
            
            
        // we going to try something... try...catch puns... XD
        // did you know there is a sausage roll day?
        // 
            
                clearScreen();
                for (int i=0; i < candidateData.length; i++){
                    System.out.println("    [" + Integer.toString(i + 1) + "] " + candidateData[i][0] + " aged " + candidateData[i][1] + " from " + candidateData[i][2] + ", with " + candidateData[i][3] + " PR disasters and " + candidateData[i][4] + " scandals.");
                    System.out.println("        Promise to country : " + candidateData[i][5]);
                    System.out.println("");
                }   
                String choice = "-1";

                
            // now we are going to try to parsing a string to integer.
            // we are going to put a try clause incase the user enters
            // an alphanumerical string or nothing at all...
            boolean lock = true;
            while (lock) {
            try {
                int convertedChoice = Integer.parseInt(choice);
                while ((Integer.parseInt(choice) <= 0 ) || (Integer.parseInt(choice) > candidateData.length)) {

                        System.out.println("[+] Please make a selection : ");
                        choice = VariableInput.nextLine();

                        // this is the part
                        // where we check if 
                        // the operator has entered 'goober'
                        // and the voting process has ended
                        if ((choice.contentEquals(closingVote)) || (choice.contentEquals("DONE"))){
                            continueVoting = false;
                            System.out.println("[+] The goober has been keyed in...");
                            System.out.println("[+] Exiting voting process...");
                            printStatistics(candidateData, votes, candidateData.length);
                            System.out.println("[+] Election complete");
                            exit(0);

                        }
                        
                        // check if the user's input is within the set range...
                        if ((Integer.parseInt(choice) <= 0 ) || (Integer.parseInt(choice) > candidateData.length)){
                            System.out.println("[!] Please stop fucking around... ");
                        }
                    }
                    votes[Integer.parseInt(choice) - 1] += 1;
                    lock = false;


                } catch (NumberFormatException e){
                // we are going to clear the screen...
                // because the idiot didn't enter a correct
                // a number instead entered an alphanumerical
                // value...
                System.out.println("[!] Please stop fucking around...");
                choice = "-1";
                }
            }
        }
        
    }
    
//  is a function that will generate a hexadecimal
//  in random with a length provided in the function
//  parameters
    static String getRandomHexString(int numchars){
        Random r = new Random();
        StringBuffer sb = new StringBuffer();
        while(sb.length() < numchars){
            sb.append(Integer.toHexString(r.nextInt()));
        }
        return sb.toString().substring(0, numchars);
    }
    
    // I made this function to print debugging stuff
    // also I like typing print
    static void printDebug(String messageInput){
        if (true){
            System.out.println(messageInput);
        }
    }
    
  // this function is used to clear the screen
  // because we need to clear the previous user's
  // choice from the next user...
    public static void clearScreen() {  
        
        // for some reason I cant clear the console
        // in netbeans...
        System.out.println("==============[ CLEARING SCREEN ]====================");
        System.out.println("");
        System.out.print("\033[H\033[2J");
        System.out.flush();


        }
    
    static String[] getVoterList(){
        // so before we can do anything we have to check if the voter has
        // the right to vote from this terminal. All thanks to Ice Bears 
        // love for fucking democracy...
        
        try {
            // first we going to declare the variables. because
            // java is such an uptight pencil pusher.
            //
            int vdl_counter = 0;
            String auth_list;
            printDebug("[+] Loading voter list...");
            auth_list = "candidates\\auth.list";
            Scanner auth_list_contents = new Scanner(new File(auth_list));
            ArrayList<String> voter_dynamic_list = new ArrayList<String>();

            // we are now loading all the contents of the
            // voter list to a dynamic array so said array
            // can be used to create a static array...
            while (auth_list_contents.hasNextLine()){
                vdl_counter += 1;
                String nextVoter = auth_list_contents.nextLine();
                voter_dynamic_list.add(nextVoter);
            }

            
            // now we are going to make a static array
            // from the dynamic array...
            String voter_static_list[] = new String[voter_dynamic_list.size()];
            for (int i = 0; i < voter_dynamic_list.size(); i++){
                voter_static_list[i] = voter_dynamic_list.get(i);
            }
            return voter_static_list;
            
            

        } catch(FileNotFoundException e){
            // exception if the auth.list file
            // is not found...
            System.out.println("[!] Error candidates\\auth.list not found...");
            exit(1);

        }
        
        // what the hell is wrong with java...
        // seriously what the fuck?
        // why do I have to tie up all loose
        // ends... ITS NOT FUCKING BANDERSNATCH!!
        String voter_static_list[] = new String[0];
        return voter_static_list;
    }

    // we are going to load some files...
    // yay...
    static String[][] loadFiles() {
        // all right so first we define the variables
        // we all do that... right? right?
        boolean fl_loop = true;
        int fl_load_counter = 0;
        int fl_parse_counter = 0;
        int feature_count = 3;
        String filename = "no_file_loaded";
        
        
        // here we are going to inititilize the 
        // ArrayList objects so they can used to dynamically append
        // items to it using add() function
        ArrayList<String> candid_name = new ArrayList<String>();
        ArrayList<String> candid_age = new ArrayList<String>();
        ArrayList<String> candid_party = new ArrayList<String>();
        ArrayList<String> candid_scandal = new ArrayList<String>();
        ArrayList<String> candid_pr = new ArrayList<String>();
        ArrayList<String> candid_promise = new ArrayList<String>();
        
        // so first we are going to into a while
        // loop where the condition is a boolean
        // variable that is set to true. Now you might
        // ask how this works...
        printDebug("[+] Loading Files...");
        
        while (fl_loop){
        // so first we are incrementing
        // the fl_load_counter. Then we are
        // going to make a filename string
            fl_load_counter += 1;
            filename = "candidates\\" + Integer.toString(fl_load_counter) + ".txt";
            
            
        // then we are going to try to open a file
        // more specifically the filename string variable
        // we just made. If its successfull we continue.
        // if it fails (aka. the file does not exist). we break
        // the loop by setting the fl_loop variable to false
            try {
                Scanner textfile_contents = new Scanner(new File(filename));

                // this counter will be used to parse the data from the
                // files. More specifically this will be incremented to determine
                // which variable is currently in the nextLine variable
                fl_parse_counter = 0;
                while (textfile_contents.hasNextLine()) {

                    // now are going to manipulate the variables
                    // that are meant to dynamically changed every loop
                    fl_parse_counter += 1;
                    String nextLine = textfile_contents.nextLine();
                    
                    // then we parse all the data
                    // into ArrayLists
                    if (fl_parse_counter == 1) {candid_name.add(nextLine);
                    } else if (fl_parse_counter == 2){candid_age.add(nextLine);
                    } else if (fl_parse_counter == 3){candid_party.add(nextLine);
                    } else if (fl_parse_counter == 4){candid_scandal.add(nextLine);
                    } else if (fl_parse_counter == 5){candid_pr.add(nextLine);
                    } else if (fl_parse_counter == 6){candid_promise.add(nextLine);}
                }
                    
            // print out a status... 
            // its good... for you mental health... I think
            
                printDebug("[+] File '" + filename + "' loaded...");
                
            } catch(FileNotFoundException e) {
                printDebug("[+] All files loaded...");
                fl_loop = false;
            }
        }
        
// so this bit is used because since it is difficult
// to pass ArrayList in return function and cannot be
// used as a global variable because they are not static,
// we'll be just parsing the ArrayList object and move all
// its contents to a new variable returnVariable which is a
// 2 dimensional array which can be easily parsed and passed
// through a for loop

        String returnVariable[][] = new String[candid_name.size()][6];
        for (int i = 0; i < candid_name.size(); i++){
            returnVariable[i][0] = candid_name.get(i);
            returnVariable[i][1] = candid_age.get(i);
            returnVariable[i][2] = candid_party.get(i);
            returnVariable[i][3] = candid_scandal.get(i);
            returnVariable[i][4] = candid_pr.get(i);
            returnVariable[i][5] = candid_promise.get(i);
        }
        printDebug("[+] File load function complete...");
        return returnVariable;
    }
    
    static void printStatistics(String candidateData[][], double votedata[], int candid_count){
        System.out.println("");
        
        // get total number of votes in election...
        int total = 0;
        for (int i = 0; i < candidateData.length; i++){
            total += votedata[i];
        }
        
        DecimalFormat df2 = new DecimalFormat("#.##");
        int highest = -22;
        int highestIndex = -1; // I'll change this to -1 to indicate that all the candidates had the came vote...
        // now that I think about it... it wont work...
        for (int i = 0; i < candidateData.length; i++){ // loop through all the candidates...
            // calculate the percentages of the voters...
            double percent;
            percent = ((votedata[i] / total) * 100);
            
            System.out.println(candidateData[i][0] + " - " + df2.format(percent) + "% (" + votedata[i] + ")");
            
            // comparing all the votes of 
            // candidates againset each other...
            if (votedata[i] > highest){
                highestIndex = i;
            }
        }
        System.out.println("");
        if (highestIndex == -1){ // checking if all the voters got the same vote...
            System.out.println("[+] Wow, its a " + candidateData.length + " way tie...");
        } else {
            // this means that that there was a great value...
            System.out.println("[+] Candidate " + candidateData[highestIndex][0] + " won. So bye...");
        }
        
        
    }
}
