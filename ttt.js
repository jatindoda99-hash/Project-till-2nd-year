let boxes=document.querySelectorAll(".box");
let resetBtn=document.querySelector("#reset-btn");
let newGameBtn=document.querySelector("#new-btn");
let msgContainer=document.querySelector(".msg-container");
let msg=document.querySelector("#msg");
let moveCount = 0; // Track how many moves are played
let turnO=true;//PlayerO, PlayerX

 /*//1d Array
let arr=["apple","banana", "litchi"];
//2d Array
let arr2=[["apple","banana"], ["potato", "mushroom"], ["pants","shirts"]];*/ 
/* Jo Upper Likha Hai Voh Sirf Explanation Hai! */
const winPatterns=[
        [0,1,2],
        [0,3,6],
        [0,4,8],
        [1,4,7],
        [2,5,8],
        [2,4,6],
        [3,4,5],
        [6,7,8],
];
const resetGame=()=>{
        turnO=true;
         moveCount = 0; // ✅ Reset moves
        enableBoxes();
        msgContainer.classList.add("hide");
}
boxes.forEach((box) => {
    box.addEventListener("click", () => {
        console.log("Box Was Clicked");

        if (turnO === true) {
            box.innerText = "O";
            turnO = false;
        } else {
            box.innerText = "X";
            turnO = true;
        }

        box.disabled= true; // ✅ Only disable the clicked box
        moveCount++;
        checkWinner();
    });
});

const disableBoxes=()=>{
                for(let box of boxes){
                                        box.disabled=true;
                }
};

const enableBoxes=()=>{
                for(let box of boxes){
                        box.disabled=false;
                        box.innerText="";
                }
};
const showWinner=(winner)=>{
                msg.innerText=`Congratulations Winner Is ${winner}`;
                msgContainer.classList.remove("hide");
}

const checkWinner=()=>{
                for(let pattern of winPatterns){
                let pos1Val=boxes[pattern[0]].innerText;
                let pos2Val=boxes[pattern[1]].innerText;
                let pos3Val=boxes[pattern[2]].innerText;

                        if(pos1Val!="" && pos2Val!="" && pos3Val!=""){
                                        if(pos1Val===pos2Val && pos2Val===pos3Val){
                                                      
                                                        showWinner(pos1Val);
                                                        disableBoxes();
                                                        return;
                                        }
                        }
                }

if (moveCount === 9) {
        msg.innerHTML = "<p>It's a Draw! </p>";
      msgContainer.classList.remove("hide"); 
    }
};

newGameBtn.addEventListener("click", resetGame);
resetBtn.addEventListener("click", resetGame);