function Get-Logo
{
    Write-Host "__      ____      ____     ___      _____ _   _ "
    Write-Host "\ \    / /\ \    / /\ \   / / |    / __//| \ | |"
    Write-Host " \ \  / /  \ \  / /  \ \_/ /| |   | | // |  \| |"
    Write-Host "  \ \/ / /\ \ \/ /    \   / | |   | |//| | . ` |"
    Write-Host "   \  / ____ \  /      | |  | |___| //_| | |\  |"
    Write-Host "    \/_/    \_\/       |_|  |______//___/|_| \_|"
    Write-Host "`n"
}

function Get-Options {
    Get-Logo

    Write-Host "Choose an option: "
    Write-Host "1. Compile and execute the application."
    Write-Host "2. How to compile."
    Write-Host "3. Get more info about the developers."
    Write-Host "4. Get more info about the project."
    Write-Host "5. Generate documentation about the project."
    Write-Host "6. Exit.`n"

    $Option = Read-Host "Your option"

    Clear-Host

    ExecuteOptions -ExecutionOption $Option
}

function Get-Compilation {
    make

    Clear-Host

    rm *.exe
    rm *.o

    Clear-Host

    Get-Options
}

function Get-Instructions {
    Get-Logo

    Write-Host "1. Dependancies"
    Write-Host "   - g++ 10.3.0 or higher;"
    Write-Host "   - make 4.3 or higher;"
    Write-Host "2. Compiling & Running"
    Write-Host "    1. Run make (For compiling)"
    Write-Host "    2. Run ./main.exe (For running)"
    Write-Host "3. Cleaning"
    Write-Host "   1. Automatically: "
    Write-Host "      - make clean"
    Write-Host "   2. Manually:"
    Write-Host "      - rm *.exe; rm *.o`n"

    Write-Host "`n1. Go Back."
    Write-Host "2. Exit.`n"

    $Option = Read-Host "Your option"

    Clear-Host

    switch($Option)
    {
        1 {Get-Options; break}
        2 {Exit;}
    }

}

function Get-Developers {
    Get-Logo

    Write-Host "Atanas Pozharliev - Scrum Master and Backend Developer."
    Write-Host "Boris Savov - Front End Developer."
    Write-Host "Kalin Chervenkov - Front End Developer."
    Write-Host "Ivelin Vasilev - QA Engineer. `n"

    Write-Host "1. Go Back."
    Write-Host "2. Exit."

    $Option = Read-Host "Your option"

    Clear-Host

    switch($Option)
    {
        1 {Get-Options; break}
        2 {Exit;}
    }
}

function Get-Info {
    Get-Logo

    Write-Host "Our project is a: " 
    Write-Host "- highly engaging," 
    Write-Host "- story-based,"
    Write-Host "- rogue-like,"
    Write-Host "- skill-based,"
    Write-Host "- speedrun-optimized," 
    Write-Host "- randomized game, related to the Babylon tower. `n"
    Write-Host "It consists of a main menu, a lobby for every floor & 2 random generated mazes for each floor.`n"
    Write-Host "Each floor has 2 mazes in it and every maze can have up to 3 types of scrolls in it. `n"

    Write-Host "1. Go To Main Menu."
    Write-Host "2. Go Next."
    Write-Host "3. Exit.`n"

    $Option = Read-Host "Your option"

    Clear-Host

    switch($Option)
    {
        1 {Get-Options; break}
        2 {Get-Storyline; break}
        3 {Exit;}
    }
}

function Get-Storyline {
    Get-Logo

    Write-Host "You are a lost adventurer. It's dark, and you can't see anything.`n"
    Write-Host "While wondering around, trying to find a way to escape the darkness,"
    Write-Host "you come around the entrance of the famous Babylon tower."
    Write-Host "Because the tower is famous for ligthing the way, you go in.`n"
    Write-Host "But before you can find your way, you need to go through series of mazes."
    Write-Host "But fear not, there are all types of scrolls left from previous adventurers to help you."
    Write-Host "`nSolve the mazes, find all the runes and light your way!`n"

    Write-Host "1. Go Back."
    Write-Host "2. Go To Main Menu"
    Write-Host "3. Exit.`n"

    $Option = Read-Host "Your option"

    Clear-Host

    switch($Option)
    {
        1 {Get-Info; break}
        2 {Get-Options; break}
        3 {Exit;}
    }

}

function Get-Documentation {
    doxygen
    ./docs\doxygen\html\index.html

    Clear-Host

    Get-Options
}

function ExecuteOptions {
    param($ExecutionOption)
    switch ($ExecutionOption)
    {
        1 {Get-Compilation; break}
        2 {Get-Instructions; break}
        3 {Get-Developers; break}
        4 {Get-Info; break}
        5 {Get-Documentation; break}
        6 {Exit}
    }
}

Get-Options

