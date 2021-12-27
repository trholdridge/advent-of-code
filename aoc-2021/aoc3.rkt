#lang racket

(require 2htdp/batch-io)
(require test-engine/racket-tests)

; Input

(define RAW-INPUT (read-lines "input3.txt"))

(define (process-input los)
  (map (λ (s) (filter number? (map string->number (string-split s "")))) los))

(define INPUT (process-input RAW-INPUT))

; --------------- PART 1 ---------------

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

; --------------- PART 2 ---------------

; most-common-bit : Nat [List-of [List-of Nat]] -> Nat
; only returns 0 or 1
(define (most-common-bit position lolon)
  (my-round (/ (foldr + 0 (map (λ (lon) (list-ref lon position)) lolon))
            (length lolon))))

(define (my-round n)
  (if (= n 0.5)
      1
      (round n)))

; keep-if-most-common : Nat [List-of [List-of Nat]] -> [List-of [List-of Nat]]
(define (keep-if-most-common position lolon)
  (local [(define COMMON (most-common-bit position lolon))]
    (filter (λ (lon) (= COMMON (list-ref lon position))) lolon)))

; keep-if-least-common : Nat [List-of [List-of Nat]] -> [List-of [List-of Nat]]
(define (keep-if-least-common position lolon)
  (local [(define COMMON (most-common-bit position lolon))]
    (filter (λ (lon) (not (= COMMON (list-ref lon position)))) lolon)))

; rating : [List-of [List-of Nat]] [keep if most/least common] -> [List-of Nat]
(define (rating lolon func)
  (foldl (λ (n filter-so-far)
           (if (= 1 (length filter-so-far))
               filter-so-far
               (func n filter-so-far)))
         lolon (build-list (length (first lolon)) values)))

; Final steps

(define (solve _)
  (* (binary->decimal (first (rating INPUT keep-if-most-common)))
     (binary->decimal (first (rating INPUT keep-if-least-common)))))