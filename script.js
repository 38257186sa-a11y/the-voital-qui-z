// Quiz data
const quizzes = {
    math: [
        { question: "What is 12 * 8?", options: ["80","96","108","112"], answer: "96" },
        { question: "Square root of 144?", options: ["10","12","14","16"], answer: "12" },
        { question: "What is 15 + 27?", options: ["40","42","44","45"], answer: "42" }
    ],
    gk: [
        { question: "Who is the Father of India?", options: ["Mahatma Gandhi","Nehru","Subhash Bose","Bhagat Singh"], answer: "Mahatma Gandhi" },
        { question: "Capital of France?", options: ["Berlin","Paris","Madrid","Rome"], answer: "Paris" },
        { question: "Which planet is called Red Planet?", options: ["Venus","Mars","Jupiter","Saturn"], answer: "Mars" }
    ]
};

let currentQuiz = [];
let currentIndex = 0;
let score = 0;

// Start quiz with selected category
function startQuiz(category) {
    currentQuiz = quizzes[category];
    currentIndex = 0;
    score = 0;
    document.getElementById("homepage").style.display = "none";
    document.getElementById("quiz-container").style.display = "block";
    showQuestion();
}

// Display question and options
function showQuestion() {
    const q = currentQuiz[currentIndex];
    document.getElementById("question").textContent = q.question;
    const optionsDiv = document.getElementById("options");
    optionsDiv.innerHTML = "";
    q.options.forEach(opt => {
        const btn = document.createElement("button");
        btn.textContent = opt;
        btn.className = "option-btn";
        btn.onclick = () => selectOption(opt);
        optionsDiv.appendChild(btn);
    });
}

// Handle option selection
function selectOption(selected) {
    if(selected === currentQuiz[currentIndex].answer) score++;
    // Disable all buttons after selection
    const buttons = document.querySelectorAll(".option-btn");
    buttons.forEach(btn => btn.disabled = true);
}

// Move to next question or finish
function nextQuestion() {
    currentIndex++;
    if(currentIndex < currentQuiz.length){
        showQuestion();
    } else {
        document.getElementById("quiz-container").style.display = "none";
        document.getElementById("result-container").style.display = "block";
        document.getElementById("score").textContent = `Your score: ${score} out of ${currentQuiz.length}`;
    }
}

// Go back to homepage
function goHome() {
    document.getElementById("result-container").style.display = "none";
    document.getElementById("homepage").style.display = "block";
}
