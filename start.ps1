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
    Write-Host "Get instructions"
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

