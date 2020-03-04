<?php
    function romanNum($input)
    {
        $roman = array(
            'M' => 1000,
            'D' => 500,
            'C' => 100,
            'L' => 50,
            'X' => 10,
            'V' => 5,
            'I' => 1
        );
        if(is_numeric($input) || strlen($input) < 1){
            return false;
        }
        // Convert the string to an array of roman values:
        for ($i = 0; $i < strlen($input); $i++){
            if(isset($roman[strtoupper($input[$i])])){
                $value[] = $roman[strtoupper($input[$i])];
            }
            else return false;
        }
        $sum = 0;
        while($current = current($value)){
            $next = next($value);
            if($current > $next){
                $sum += $current;
            }else{
                $sum -= $current;
            }
        }
        return $sum;
    }
    function isRoman($str){
        $romans = "IVXLCDM";
        $len = strlen($str);
        for ($i = 0; $i < $len; $i++){
            if (strpos($romans, $str[$i]) !== false)
            $i++;
        else
            return false;
        }
        return true;
    }


    function test($input){
        if(is_numeric($input)){
            if(!romanNum($input)){
                echo "input should be String, number is not acceptable. Pass number test. "."<br>";
            }

        }
        else if($input == ""){
            if(!romanNum($input)){
                echo  "input is nothing, please provide valid String. Pass empty string test"."<br>";
            }
        }
        else if(strstr($input," ")){
            if(!romanNum($input)){
                echo "input contains space, please remove. Pass space test"."<br>";
            }
        }
       else if(!isRoman($input)){
           if(!romanNum($input)){
               echo  "input should combine with I,V,X,L,C,D,M. Pass meaningless string test."."<br>";
           }
        }
        else echo "input: $input, output: ".romanNum($input)." input covers correctly, Pass test."."<br>";

    }
test(123);
test("");
test("    ");
test("llyloveyou");
test("MCMXC");
test("VI");
test("IX");
test("IV");
    ?>

