;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-intermediate-lambda-reader.ss" "lang")((modname aoc3) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f () #f)))
(require 2htdp/batch-io)
(require racket/string)

(define RAW-INPUT (read-lines "input3.txt"))

(define (process-input los)
  (map (λ (s) (filter number? (map string->number (string-split s "")))) los))

(define INPUT (process-input RAW-INPUT))

; gamma : [List-of [List-of Nat]] -> [List-of Num]
(check-expect (gamma (list (list 1 0 0 0 0)
                           (list 1 1 0 0 0)
                           (list 1 1 1 0 0)
                           (list 1 1 1 1 0)))
              (list 1 0.75 0.5 0.25 0))
(define (gamma lolon)
  (local [; get-bit : Nat -> [List-of Nat]
          (define (get-bit list-access)
            (/ (foldr (λ (lon so-far) (+ (list-ref lon list-access) so-far)) 0 lolon)
               (length lolon)))]
    (build-list (length (first lolon)) (λ (n) (get-bit n)))))

; epsilon : [List-of Num] -> [List-of Num]
(define (epsilon gamma)
  (map (λ (g) (- 1 g)) gamma))

; list->binary : [List-of Num] -> [List-of Nat]
(define (list->binary probabilities)
  (map round probabilities))

; binary->decimal : [List-of Nat] -> Nat
(check-expect (binary->decimal (list 1 1 0 0 1)) 25)
(define (binary->decimal lon)
  (foldr + 0
         (build-list (length lon)
                     (λ (n) (* (expt 2 (- (length lon) (+ n 1)))
                               (list-ref lon n))))))

; -------------------------------------------------------

; most-common-bit : Nat [List-of [List-of Nat]] -> Nat
; only returns 0 or 1
(define (most-common-bit position lolon)
  (round (/ (foldr + 0 (map (λ (lon) (list-ref position lon)) lolon))
            (length lolon))))

; keep-if-most-common : Nat [List-of [List-of Nat]] -> [List-of [List-of Nat]]
(define (keep-if-most-common bit position lolon)
  (filter (λ (lon) (= bit (list-ref position lon))) lolon))

; keep-if-least-common : Nat [List-of [List-of Nat]] -> [List-of [List-of Nat]]
(define (keep-if-least-common bit position lolon)
  (filter (λ (lon) (not (= bit (list-ref position lon)))) lolon))