Write-Host "[+] Ejecutando 'make clean'"
& make clean

Write-Host "[+] Ejecutando 'make':"
& make

if ($LASTEXITCODE -ne 0)
{
    Write-Host "[-] Error al ejecutar 'make'. Deteniendo script."
    exit
}

$exeMasReciente = 
    Get-ChildItem -Path .\bin -Filter *.exe | 
    Sort-Object LastWriteTime -Descending | 
    Select-Object -First 1

if ($exeMasReciente)
{
    Write-Host "[+] Ejecutando programa:"
    & $exeMasReciente
}
else
{
    Write-Host "[-] Ejecutable no encontrado."
}
