;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-intermediate-lambda-reader.ss" "lang")((modname aoc7) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f () #f)))
(require 2htdp/batch-io)
(require racket/string)

(define RAW-INPUT (read-file "input7.txt"))
(define INPUT (map string->number (string-split RAW-INPUT ",")))

(define MIN (foldr min (first INPUT) (rest INPUT)))
(define MAX (foldr max (first INPUT) (rest INPUT)))

; ----------------------
; PART 1
; ----------------------

; min-fuel : [List-of Nat] Nat Nat
; finds the x position which takes least fuel to move all the crabs to
(define (min-fuel lon min-x max-x)
  (local [; cost-of : Nat -> Nat
          ; finds the cost of an x position for the crabs to move to
          ; 1 fuel per unit of movement
          (define (cost-of x)
            (foldr (λ (crab so-far) (+ so-far (abs (- crab x)))) 0 lon))]
    (foldr (λ (x min-so-far) (min (cost-of x) min-so-far))
           (cost-of max-x) (build-list (- max-x min-x) (λ (n) (+ n min-x))))))


; ----------------------
; PART 2
; ----------------------

; min-fuel/v2 : [List-of Nat] Nat Nat
; finds the x position which takes least fuel to move all the crabs to
(define (min-fuel/v2 lon min-x max-x)
  (local [; cost-of : Nat -> Nat
          ; finds the cost of an x position for the crabs to move to
          ; fuel per movement calculated with a helper
          (define (cost-of x)
            (foldr (λ (crab so-far) (+ so-far (cost-of-move crab x))) 0 lon))]
    (foldr (λ (x min-so-far) (min (cost-of x) min-so-far))
           (cost-of max-x) (build-list (- max-x min-x) (λ (n) (+ n min-x))))))

; cost-of-move : Nat Nat -> Nat
; first unit is 1 fuel, second is 2, etc
(define (cost-of-move crab position)
  (local [(define DISTANCE (abs (- crab position)))]
    (if (zero? DISTANCE)
        0
        (/ (* DISTANCE (+ DISTANCE 1)) 2)))) ; sum of numbers from 1 to DISTANCE