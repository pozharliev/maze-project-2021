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
    Clear-Host

    Get-Logo

    Write-Host "Choose an option: "
    Write-Host "1. Compile and execute the application."
    Write-Host "2. How to compile."
    Write-Host "3. Get more info about the developers and the project."
    Write-Host "4. Generate documentation about the project."
    Write-Host "5. Exit.`n"

    $Option = Read-Host "Your option"

    Clear-Host

    ExecuteOptions -ExecutionOption $Option
}

function Get-Compilation {
    make
    Clear-Host
    rm *.exe
    rm *.o
    Get-Options
}

function Get-Instructions {
    Write-Host "Get instructions"
    Get-Options
}

function Get-Info {
    Write-Host "Get info"
    Get-Options
}

function Get-Documentation {
    doxygen
    ./docs\doxygen\html\index.html
    Get-Options
}

function ExecuteOptions {
    param($ExecutionOption)
    switch ($ExecutionOption)
    {
        1 {Get-Compilation; break}
        2 {Get-Instructions; break}
        3 {Get-Info; break}
        4 {Get-Documentation; break}
        5 {Exit}
    }
}





Get-Options

