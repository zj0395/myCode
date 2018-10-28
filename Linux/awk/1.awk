BEGIN{
FS=":";
}
{
    sub(/ */,"", $2) # delete the space in the front of $2
    if($1=="username")
    {
        if($2 ~/[1-9]{11}/) # phone only
        {
            result=$2;
            flag=1
        }
        else
        {
            result=""
            flag=0
        }
    }
    else if($1=="propery" && flag==1)
    {
        result=result"\t"$2; # str+str
    }
    else if(NR%4==0 && flag==1)
    {
        result=result"\t"$0; # str+str
        print result
    }
}
END{
}
