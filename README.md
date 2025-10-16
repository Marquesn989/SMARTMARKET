# SMARTMARKET

SMARTMARKET é um protótipo de "supermercado inteligente" desenvolvido em C++ com raylib.

## Estrutura

- `src/` - código-fonte C++
- `include/` - headers organizados (product, catalog, cart, receipt)
- `data/catalog.txt` - catálogo de exemplo (formato: id;nome;preço)
- `build/` - executável gerado
- `output/` - recibos gerados

## Como compilar (Windows, MinGW)

- Edite `Makefile` se necessário para apontar `RAYLIB_DIR` para a sua instalação local do raylib.
- No PowerShell, execute:

```powershell
# Compilar
C:/Users/a35560/AppData/Local/Microsoft/WinGet/Packages/BrechtSanders.WinLibs.MCF.UCRT_Microsoft.Winget.Source_8wekyb3d8bbwe/mingw64/bin/mingw32-make.exe all

# Executar (ajuste o PATH para encontrar raylib.dll)
$env:PATH='C:/Users/a35560/SmartMarket/raylib/lib;'+$env:PATH; .\build\smartmarket.exe
```

## Como usar

- Clique num produto no catálogo para adicionar ao carrinho.
- Clique num item do carrinho para removê-lo.
- Clique em Checkout para salvar um recibo em `output/receipt_YYYYMMDD_HHMMSS.txt` e limpar o carrinho.
- Pressione ESC para sair.

## Próximos passos sugeridos

- Melhorar UI/UX e adicionar imagens de produtos.
- Implementar persistência do carrinho e contas de utilizador.
- Internacionalização e configuração de moeda.
