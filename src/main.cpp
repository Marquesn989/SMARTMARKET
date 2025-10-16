#include "raylib.h"
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include "../include/catalog.h"
#include "../include/cart.h"
#include "../include/receipt.h"

int main() {
    const int screenWidth = 1000;
    const int screenHeight = 700;

    InitWindow(screenWidth, screenHeight, "SmartMarket - SMARTMARKET");
    SetTargetFPS(60);

    Color brandBlue = { 10, 36, 99, 255 };

    Catalog catalog;
    bool loaded = catalog.loadFromFile("data/catalog.txt");
    if (!loaded) {
        // fallback: small hardcoded catalog
        std::cerr << "Aviso: não foi possível carregar data/catalog.txt. Usando catálogo padrão.\n";
    }

    Cart cart;

    const Rectangle checkoutBtn = { 860, 620, 110, 48 };

    std::string lastReceiptMsg;
    int receiptMsgTimer = 0; // frames

    while (!WindowShouldClose()) {
        Vector2 mousePoint = GetMousePosition();
        // Build a stable display order for cart items (map iteration order is not deterministic)
        std::vector<int> cartOrder;
        cartOrder.reserve(cart.items().size());
        for (const auto &kv : cart.items()) cartOrder.push_back(kv.first);

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
            // Click catalog (add one)
            const auto &products = catalog.products();
            for (size_t i = 0; i < products.size(); ++i) {
                Rectangle r = { 20.0f, 100.0f + float(i) * 64.0f, 480.0f, 56.0f };
                if (CheckCollisionPointRec(mousePoint, r)) {
                    cart.add(products[i].id);
                }
            }

            // Click cart items: left-click removes one unit; Shift+click removes all units
            for (size_t i = 0; i < cartOrder.size(); ++i) {
                Rectangle r = { 520.0f, 100.0f + float(i) * 44.0f, 440.0f, 38.0f };
                if (CheckCollisionPointRec(mousePoint, r)) {
                    int pid = cartOrder[i];
                    bool shift = IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT);
                    if (shift) cart.removeAll(pid);
                    else cart.removeOne(pid);
                    break;
                }
            }

            if (CheckCollisionPointRec(mousePoint, checkoutBtn)) {
                std::string fname = saveReceipt(cart, catalog);
                cart.clear();
                if (!fname.empty()) {
                    lastReceiptMsg = std::string("Recibo gravado: ") + fname;
                } else {
                    lastReceiptMsg = "Erro ao gravar recibo";
                }
                receiptMsgTimer = 240; // show for ~4 seconds at 60fps
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Header
        DrawRectangle(0, 0, screenWidth, 88, brandBlue);
        DrawText("SMARTMARKET", 18, 26, 36, RAYWHITE);
        DrawText("Supermercado Inteligente — clique num produto para adicionar; clique no carrinho para remover", 220, 34, 14, RAYWHITE);

        // Catalog
        DrawText("Catálogo:", 20, 74, 22, DARKBLUE);
        const auto &products = catalog.products();
        for (size_t i = 0; i < products.size(); ++i) {
            float y = 100.0f + float(i) * 64.0f;
            Rectangle r = { 20.0f, y, 480.0f, 56.0f };
            DrawRectangleRec(r, (i % 2 == 0) ? Fade(SKYBLUE, 0.25f) : Fade(LIGHTGRAY, 0.08f));
            DrawText(products[i].name.c_str(), int(r.x) + 12, int(r.y) + 10, 20, DARKBLUE);
            char priceBuf[32];
            sprintf(priceBuf, "€ %.2f", products[i].price);
            DrawText(priceBuf, int(r.x) + 12, int(r.y) + 32, 16, GRAY);
            DrawText("(Clique para adicionar)", int(r.x) + 320, int(r.y) + 18, 14, DARKGREEN);
        }

        // Cart
        DrawText("Carrinho:", 520, 74, 22, DARKBLUE);
        const auto &itemsMap = cart.items();
        // rebuild order for drawing (same order used for click detection)
        std::vector<int> drawOrder;
        drawOrder.reserve(itemsMap.size());
        for (const auto &kv : itemsMap) drawOrder.push_back(kv.first);
        for (size_t i = 0; i < drawOrder.size(); ++i) {
            int pid = drawOrder[i];
            int qty = itemsMap.at(pid);
            const Product* p = catalog.findById(pid);
            float y = 100.0f + float(i) * 44.0f;
            Rectangle r = { 520.0f, y, 440.0f, 38.0f };
            DrawRectangleRec(r, Fade(LIGHTGRAY, 0.12f));
            if (p) {
                char line[256];
                sprintf(line, "%s x%d - € %.2f", p->name.c_str(), qty, p->price * qty);
                DrawText(line, int(r.x) + 10, int(r.y) + 8, 18, DARKBLUE);
                DrawText("(Clique para remover 1; Shift+Clique remove tudo)", int(r.x) + 10, int(r.y) + 22, 12, MAROON);
            }
        }

        // Total and checkout
        char totalBuf[64];
        sprintf(totalBuf, "Total: € %.2f", cart.total(catalog));
        DrawText(totalBuf, 520, 630, 26, DARKBLUE);

        DrawRectangleRec(checkoutBtn, Fade(GREEN, 0.08f));
        DrawRectangleLines(int(checkoutBtn.x), int(checkoutBtn.y), int(checkoutBtn.width), int(checkoutBtn.height), DARKGREEN);
        DrawText("Checkout", int(checkoutBtn.x) + 12, int(checkoutBtn.y) + 10, 20, DARKGREEN);

        DrawText("ESC para sair", 20, screenHeight - 28, 18, GRAY);
        if (receiptMsgTimer > 0 && !lastReceiptMsg.empty()) {
            DrawRectangle(200, screenHeight - 70, 600, 40, Fade(SKYBLUE, 0.25f));
            DrawText(lastReceiptMsg.c_str(), 220, screenHeight - 64, 18, DARKBLUE);
            receiptMsgTimer--;
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}