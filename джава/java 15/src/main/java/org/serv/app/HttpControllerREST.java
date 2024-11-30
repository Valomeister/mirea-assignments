package org.serv.app;

import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.Objects;

@RestController
public class HttpControllerREST {
    List<String> history = new ArrayList<>();

    // Обработка тела JSON-запроса
    @PostMapping("/")
    public ResponseEntity<?> calculateJson(@RequestBody Map<String, Object> body) {
        try {
            // Извлекаем данные из JSON
            double a = ((Number) body.get("a")).doubleValue();
            double b = ((Number) body.get("b")).doubleValue();
            String operation = (String) body.get("operation");

            // Выполняем операцию
            double result = performOperation(operation, a, b);
            String log = operation + "(" + a + ", " + b + ") = " + result;
            history.add(log);
            return ResponseEntity.ok(result);

        } catch (NullPointerException | ClassCastException e) {
            return ResponseEntity.badRequest().body("Некорректные данные JSON. Формат: {a:число, b:число, operation:\"операция\"}");
        } catch (IllegalArgumentException e) {
            return ResponseEntity.badRequest().body(e.getMessage());
        }
    }


    @GetMapping("/history")
    public ResponseEntity<List<String>> getHistory() {
        return ResponseEntity.ok(history);
    }

    @GetMapping("/{operation}")
    public String operate(@PathVariable String operation, @RequestParam(required = true) double a,
                         @RequestParam(required = true) double b) {
        if (Objects.equals(operation, "div") && b == 0) return "Ошибка: деление на 0";
        double result = performOperation(operation, a, b);
        String log = operation + "(" + a + ", " + b + ") = " + result;
        history.add(log);
        return log;

    }

    double performOperation(String operation, double a, double b) {
        double result;
        switch (operation) {
            case "add":
                result = a + b;
                break;
            case "sub":
                result = a - b;
                break;
            case "mul":
                result = a * b;
                break;
            case "div":
                if (b != 0) {
                    result = a / b;
                } else {
                    // Обработка деления на 0 (например, выбрасывание исключения)
                    throw new IllegalArgumentException("Cannot divide by zero");
                }
                break;
            default:
                result = 0; // Возвращаем 0 по умолчанию
                break;
        }
        return result;
    }


}
