;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-intermediate-lambda-reader.ss" "lang")((modname aoc4) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f () #f)))
(require 2htdp/batch-io)
(require 2htdp/image)
(require 2htdp/universe)
(require racket/list)
(require racket/string)

; Input

(define RAW-INPUT (read-lines "input4.txt"))
(define DRAWS (map string->number (string-split (first RAW-INPUT) ",")))

(define-struct bingo [row-wise col-wise])
; A Bingo is a (make-bingo [List-of [List-of Nat]] [List-of [List-of Nat]])
; - where row-wise is the list of numbers on the board by row
; - col-wise is the list of numbers on the board by column
; and represents a board for a game of bingo

; split-into-boards : [List-of String] -> [List-of [List-of String]]
(check-expect (split-into-boards (list "1")) (list (list "1")))
(check-expect (split-into-boards (list "1" "2" "" "3" "4" "5"))
              (list (list "1" "2") (list "3" "4" "5")))
(define (split-into-boards los)
  (foldr (λ (str boards-so-far)
           (if (string=? str "")
               (cons '() boards-so-far)
               (cons (cons str (first boards-so-far))
                     (rest boards-so-far))))
         (list '()) los))

; strings->board : [List-of String] -> Bingo
(check-expect (strings->board '("1" "2"))
              (make-bingo (list (list 1) (list 2)) (list (list 1 2))))
(check-expect (strings->board '("1 2  3" " 4 5   6"))
              (make-bingo (list (list 1 2 3) (list 4 5 6))
                          (list (list 1 4) (list 2 5) (list 3 6))))
(define (strings->board los)
  (local [(define ROWS
            (map (λ (s) (map string->number (string-split s #rx"  *"))) los))]
    (make-bingo ROWS (apply map list ROWS)))) ; transpose ROWS to get columns

; final input transformation
(define INPUT (map strings->board (split-into-boards (rest (rest RAW-INPUT)))))


; --------------- PART 1 ---------------

(define-struct world [draws boards])

; play-until-win : _ -> World
(define (play-until-win _)
  (big-bang (make-world DRAWS INPUT)
    [to-draw (λ (w) (empty-scene 200 200))]
    [on-tick draw-next]
    [stop-when is-winning-board? draw-final-score]))

; draw-next : World -> World
(define (draw-next w)
  (local [(define N (first (world-draws w)))
          (define (filter-board b)
            (make-bingo (map filter-row (bingo-row-wise b))
                        (map filter-row (bingo-col-wise b))))
          (define (filter-row r)
            (filter (λ (x) (not (= x N))) r))]
    (make-world (rest (world-draws w))
                (map filter-board (world-boards w)))))

; is-winning-board? : World -> Boolean
(define (is-winning-board? w)
  (ormap winning-board? (world-boards w)))

; winning-board? : Board -> Boolean
(define (winning-board? b)
            (or (ormap (λ (row) (empty? row)) (bingo-row-wise b))
                (ormap (λ (col) (empty? col)) (bingo-col-wise b))))

; draw-final-score : World -> Image
(define (draw-final-score w)
  (local [(define WINNER (first (filter winning-board? (world-boards w))))
          (define (score w)
            (* (apply + (flatten (bingo-row-wise WINNER)))
               (list-ref DRAWS (- (length DRAWS) (length (world-draws w)) 1))))]
    (overlay (text (number->string (score w)) 24 "black")
             (empty-scene 200 200))))

; --------------- PART 2 ---------------
; this is terrible but I just print the board and remaining draws
; when there's only one board left and then calculate by hand

; play-until-last : _ -> World
(define (play-until-last _)
  (big-bang (make-world DRAWS INPUT)
    [to-draw (λ (w) (empty-scene 500 500))]
    [on-tick draw-next]
    [stop-when is-last-board? draw-last-board]))

; is-last-board? : World -> Boolean
(define (is-last-board? w)
  (= 1 (length (filter (λ (b) (not (winning-board? b)))
                                      (world-boards w)))))

; draw-last-board : World -> Image
(define (draw-last-board w)
  (local [(define LAST (first (filter (λ (b) (not (winning-board? b)))
                                      (world-boards w))))
          (define (draw-lon lon)
            (foldr (λ (n img)
                     (beside (text (string-append (number->string n) " ")
                                   24 "black")
                             img))
                   empty-image lon))]
    (above (draw-lon (world-draws w))
           (foldr (λ (lon img) (above (draw-lon lon) img))
                  empty-image (bingo-row-wise LAST))
           (foldr (λ (lon img) (above (draw-lon lon) img))
                  empty-image (bingo-col-wise LAST)))))