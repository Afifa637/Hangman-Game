<!DOCTYPE html>
<html>
<head>
    <title>Hangman Game - ReadMe</title>
</head>
<body>

<h1>Hangman Game</h1>
<p>This project implements a simple Hangman Game using C++ concepts such as:</p>

<ul>
    <li><strong>Abstract Class</strong> - The <code>Game</code> class is abstract with a pure virtual function <code>Play()</code>, ensuring that all derived classes implement this method.</li>
    <li><strong>Polymorphism (Runtime)</strong> - The <code>Play()</code> function is overridden in the derived class <code>HangmanGame</code>, showcasing runtime polymorphism.</li>
    <li><strong>Operator Overloading</strong> - The <code>&lt;</code> operator is overloaded for the <code>MyPair</code> class to allow custom comparison in sorting the leaderboard.</li>
    <li><strong>File Handling</strong> - The game uses file operations to load words from a file and save player scores in a leaderboard.</li>
    <li><strong>Friend Function and Friend Class</strong> - The <code>MyPair</code> class uses a friend function and declares the <code>Game</code> class as its friend to allow direct access to private members.</li>
    <li><strong>Template Class</strong> - The <code>MyPair</code> class is a template class, allowing flexibility in storing pairs of different types.</li>
    <li><strong>STL Vector and Pair</strong> - The Standard Template Library (STL) is used to store guessed letters and to handle the leaderboard with pairs of names and scores.</li>
</ul>

<h2>How to Play</h2>
<ol>
    <li>Guess one letter at a time to figure out the secret word.</li>
    <li>If your guess is incorrect, a part of the hangman is drawn.</li>
    <li>Win by guessing the word before the full hangman is drawn.</li>
</ol>

<h2>Instructions</h2>
<ul>
    <li>Press '1' to start a new game.</li>
    <li>Press '2' to view instructions.</li>
    <li>Press '3' to view the leaderboard.</li>
    <li>Press '4' to quit the game.</li>
</ul>

<h2>Leaderboard</h2>
<p>The game stores player scores in a file and displays a sorted leaderboard based on performance.</p>

<h2>Requirements</h2>
<ul>
    <li>Make sure the file <code>word.txt</code> contains words for the game to choose from.</li>
    <li>Ensure that <code>leaderboard.txt</code> exists to store the leaderboard data.</li>
</ul>

</body>
</html>
