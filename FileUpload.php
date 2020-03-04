<?php
    echo<<<_END
                <html><head><title>PHP Form Upload</title></head><body>
                <form method='post' action='FileUpload.php' enctype='multipart/form-data'>
                        Select File: <input type="file" name="filename" size="10">
                        <input type="submit" value="Upload">
                        </form>
_END;

    function readData($name){
        $file = fopen($name, "r");
        $data=array();
        $i=0;
        $number = array("0","1","2","3","4","5","6","7","8","9");
        $isAllInt = true;
        while(! feof($file)){
            $str = fgetc($file);
            $ch = ord($str);
            if($ch != 10 && $ch != 13 && $ch != 32){
                $data[$i]= $str;
                if (!in_array($data[$i], $number)){
                    $data = array("This file contains other symbol, file close");
                    $isAllInt = false;
                    break;
                }
                $i++;
            }
        }
        fclose($file);
        //for($i = 0; $i < sizeof($data); $i++){        }

        if($isAllInt){
            if(sizeof($data) < 1000){
                $data = array("This file contains less than 1000 numbers, file close");
            }
        }

        return $data;

    }

    function maxProduct($data){
        $size = sizeof($data);
        $start = 0;
        $end = $size-1;
        $max = 0;
        for($i = 0; $i < $size; $i++){

            $start = $i;
            $end = $start + 5 - 1;
            if($end < $size){
                $current = (int)($data[$start])*(int)($data[$start+1])*(int)($data[$start+2])*(int)($data[$start+3])*(int)($data[$end]);
            }else{
                $current = (int)($data[$size-1])*(int)($data[$size-2])*(int)($data[$size-3])*(int)($data[$size-4])*(int)($data[$size-5]);
            }

            if ($current >= $max){
                $max = $current;
            }
        }




        return $max;

    }

    function sumOfFactorial($max){
        $result = str_split($max);
        $allSum = 0;
        for($i = 0; $i < sizeof($result); $i++){
            $sum = factorial($result[$i]);
            $allSum += $sum;
        }

        return $allSum;

    }


    function factorial($a)
    {
        if ($a > 1) {
            $r = $a * factorial($a - 1);
        } else {
            $r = $a;
        }
        return $r;
    }


        if($_FILES){
        $name = $_FILES["filename"]["name"];
        $type = $_FILES["filename"]["type"];
        $size = $_FILES["filename"]["size"];
        $tmp_name =  $_FILES["filename"]["tmp_name"] ;

        $suffix = pathinfo($_FILES["filename"]['name'],PATHINFO_EXTENSION);
        $allow = array("txt");
        $isTxt = false;
        if(in_array($suffix,$allow)){
            //not allowed type
            $isTxt = true;
        }
        if($isTxt){
            move_uploaded_file($tmp_name,$name);
            echo "Update Successfully"."<br />";
            echo "Upload: " .$name . "<br />";
            echo "Type: " . $type . "<br />";
            echo "Size: " . $size. " b<br />";
            echo "Stored in: " ."D:\PhpStorm\WorkSpace\HW3\upload"."<br />";
            echo "Upload Text '$name'<br><txt src ='$name'>";

            //read data from updated file.
            $data = readData($name);
            //print_r($data);


            echo "The Max result is: ".maxProduct($data)."<br />";

            echo "The sum of factorial for such number is : ".sumOfFactorial(maxProduct($data))."<br />";



        }
        else{
            echo  'Upload fail, This is not TXT file';
        }



    }
    echo "</body></html>";

        function maxProductTest(){
            $test = array(1,2,3,4,5,6);
            echo "input is: ";
            print_r($test);
            $r = maxProduct($test);
            if($r == 720){
                echo  "output is: ".$r."<br>";
                echo "maxProduct pass the test"."<br>";
            }
            else{
                echo "maxProduct is wrong";
            }
        }
        function SumOfFactorialTest(){
            $test = 1234;
            $r = sumOfFactorial($test);
            if($r == 33){
                echo "input is: ".$test."<br>";
                echo  "output is: ".$r."<br>";
                echo "SumOfFactorial pass the test"."<br>";
            }
            else{
                echo "sum of factorial is wrong";
            }
        }
        maxProductTest();
        SumOfFactorialTest();
