
var letters = ["G","I", "L", "A", "D"];
var clickedSquares = [];
var firstSquare = null;
var fontSize=40;


function add_squares(sqrSize, amount) {
    const L3Squares = document.getElementsByClassName("L3Squares")[0];
    for (let i = 0; i < amount; i++, sqrSize += 20,fontSize+=15) {
        let square = document.createElement("article");
        let letter = "<p class=cardLetter amiko style=font-size:"+fontSize+"px>" + generate_letter() + "</p>";
        square.style.width = sqrSize + "px";
        square.style.height = sqrSize + "px";
        square.style.backgroundColor = "#000000";
        square.innerHTML = letter;
        L3Squares.appendChild(square);

        square.addEventListener("click", () => {
            let cardLetter = square.getElementsByClassName("cardLetter")[0];
            if (cardLetter == firstSquare)
                return;
            cardLetter.style.visibility = "visible";
            clickedSquares.push(cardLetter);
            if (clickedSquares.length == 1) {
                firstSquare = cardLetter;
            }
            if (clickedSquares.length == 2) {
                if (cardLetter.textContent != firstSquare.textContent) {
                    setTimeout(function () {
                        cardLetter.style.visibility = "hidden";
                        firstSquare.style.visibility = "hidden";
                        firstSquare = null;
                    }, 1000);
                }
                if (cardLetter.textContent == firstSquare.textContent) {
                    color = random_color()
                    cardLetter.parentElement.style.backgroundColor = color;
                    firstSquare.parentElement.style.backgroundColor = color;
                }
                clickedSquares.length = 0;
            }
            if (clickedSquares.length > 2) {
                for (var i = 0; i < clickedSquares.length; i++) {
                    clickedSquares[i].style.visibility = "hidden"
                }
                firstSquare = null;
                clickedSquares.length = 0;
            }



        });

    }
}


function initalize() {
    add_squares(80, 7)
}

var size = 160;
function add_squares_click() {
    size += 60;
    add_squares(size, 3);
}

function random_color() {
    var x = Math.floor(Math.random() * 256);
    var y = Math.floor(Math.random() * 256);
    var z = Math.floor(Math.random() * 256);
    return "rgb(" + x + "," + y + "," + z + ")";

}

function generate_letter() {
    return letters[Math.floor(Math.random() * letters.length)];
}