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
    Write-Host "Choose an option: "
    Write-Host "1. Compile and execute the application."
    Write-Host "2. How to compile."
    Write-Host "3. Get more info about the developers and the project."
    Write-Host "4. Exit.`n"
}

function Compile-AndRun {
    make
}

function Get-Instructions {
    Write-Host "Get instructions"
}

function Get-Info {
    Write-Host "Get info"
}

function ExecuteOptions {
    param($ExecutionOption)
    switch ($ExecutionOption)
    {
        1 {Compile-AndRun; break}
        2 {Get-Instructions; break}
        3 {Get-Info; break}
        4 {Exit}
    }
}

Clear-Host

Get-Logo

Get-Options

$Option = Read-Host "Your option"

Clear-Host

ExecuteOptions -ExecutionOption $Option
