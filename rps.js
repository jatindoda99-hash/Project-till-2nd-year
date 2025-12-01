let userScore=0;
let compScore=0;

const choices=document.querySelectorAll(".choice");
const msg=document.querySelector("#msg");

const userScorePara=document.querySelector("#user-score");
const compScorePara=document.querySelector("#comp-score");
const genCompChoice=()=>{
   const options=["rock","paper","scissors"];
    //Rock Paper Scissor 
    //We HAve To Store THese Choices In An Array 
    const randIdx=Math.floor(Math.random() *3);
    return options[randIdx];

};
//For Draw Game Fucntion
const drawGame=()=>{
    console.log("Game Was Draw");
    msg.innerText="Game Was Draw. Play Again!";
        msg.style.backgroundColor="#081b31";
}

//For ShowWinner
const showWinner=(userWin,userChoice,compChoice)=>{
    if(userWin===true)
                {   
                        userScore++; //If User Win UserScore Will Updated 
                        userScorePara.innerText=userScore;
                    console.log("you Win!");
                    msg.innerText=`You Win! Your ${userChoice} Beats ${compChoice}`;
                    msg.style.backgroundColor="green";
                }
    else{
        compScore++;
        compScorePara.innerText=compScore;//If User Lose COmputer Score Will Updated 
        console.log("You Lose!");
       msg.innerText=`You Lose! ${compChoice} Beats Your ${userChoice}`;
         msg.style.backgroundColor="red";
    }
}
const playGame=(userChoice)=>{
    console.log("userChoice=",userChoice);
    //To Generate Computer Choice -> Modularity 
    /*No We Will Create One Variable Named As compChoice Which Will Store the Value 
    Returned By genCompChoice Function */
    const compChoice=genCompChoice();
    console.log("Computer Choice=",compChoice);
    //Draw Condition And We Are Using If-else ladder 
    if(userChoice===compChoice)
    {
        //Draw Game
        drawGame(); //We Will Call This Fucntion Because This Will Display Some Msg 
    }
    else{
        let userWin=true;
        if(userChoice==="rock")
        {
            //Computer Choice WIll be Paper ANd Scissor
            userWin=compChoice==="paper"?false:true; //If Scissor Then USer Will Win
        }
        else if(userChoice==="paper")
        {
            //Computer Choice Will Be Rock And Scissor
          userWin=compChoice==="scissors"?false:true;// Rock Hui Toh True 
        }
        //Now user Will Take Scissor
        else
        {
            // COmputer Will Hae Rock ANd Paper
           userWin=compChoice==="rock"?false:true; //If Scissor Hai Toh user Jitega
        }
        showWinner(userWin,userChoice,compChoice);
    }
};

choices.forEach((choice)=>{
    choice.addEventListener("click",()=>{
        const userChoice=choice.getAttribute("id");
        playGame(userChoice); //Yeh Pass Ki Function ma
    });
});