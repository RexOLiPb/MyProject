<?php
    function findPrime($input){

        $current = 2;
        $isPrime = True;
        $output = array();
        if($input <= 1){
            $isPrime = false;
            $current = 1;
           $output[0] = false;
        }

        while($current != $input){
            if($isPrime){
                for($i = 2; $i < $current; $i++){
                    if($current % $i == 0){
                        $isPrime = False;
                    }
                }
            }
            if($isPrime){
                array_push($output, $current);
            }
            $current++;
            $isPrime = True;
        }
        return $output;
    }

function test10(){
        $output = findPrime(10);
        $testValue = array(2,3,5,7);
        $compare = array();
        if(sizeof($output) == sizeof($testValue)){
            $compare = array_diff($output, $testValue);
        }

        if(sizeof($compare) == 0) {
            echo 'Finding prime number up to 10 pass the test.</br>'."\xA";
            echo 'Here is result； </br>'."\xA";
            print_r($output);
            echo '</br>';
        }

}

function test100(){
    $output = findPrime(100);
    $testValue = array(2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97);
    $compare = array();
    if(sizeof($output) == sizeof($testValue)){
        $compare = array_diff($output, $testValue);
    }

    if(sizeof($compare) == 0) {
        echo 'Finding prime number up to 100 pass the test.</br>'."\xA";
        echo 'Here is result: </br>'."\xA";
        print_r($output);
        echo '</br>';
    }
}

function test1(){
    $output = findPrime(1);
    if(!$output[0]){
        echo '0 and 1 are both not prime number.</br>'."\xA";
    }
}

test10();
test100();
test1();
