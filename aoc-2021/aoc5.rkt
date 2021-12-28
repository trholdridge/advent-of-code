;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-intermediate-lambda-reader.ss" "lang")((modname aoc5) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f () #f)))
(require 2htdp/batch-io)
(require racket/string)
(require racket/list)

; Input

(define POSN1 (make-posn 0 0))
(define POSN2 (make-posn 0 3))
(define POSN3 (make-posn 2 3))

(define-struct line [start end])
; a Line is a (make-struct Posn Posn)
; - where start is the first point in the line
; - and end is the last
; representing a line of vapors for the submarine to navigate
(define LINE1 (make-line (make-posn 0 0) (make-posn 0 3)))
(define LINE2 (make-line (make-posn 0 3) (make-posn 2 3)))
(define LINE3 (make-line (make-posn 7 1) (make-posn 9 1)))
; line-temp : Line -> ???
(define (line-temp l)
  (... (line-start l)
       (line-end l)))

(define (process-input los)
  (map process-line los))

(define (process-line s)
  (local [(define SPLIT (string-split s " "))]
    (make-line (process-posn (first SPLIT))
               (process-posn (second SPLIT)))))

(define (process-posn s)
  (local [(define SPLIT (string-split s ","))]
    (make-posn (string->number (first SPLIT))
               (string->number (second SPLIT)))))

(define (max-posn access lol)
  (foldr (λ (line max-so-far) (max (access (line-start line))
                                   (access (line-end line))
                                   max-so-far))
         0 lol))

(define RAW-INPUT (read-lines "input5.txt"))
(define INPUT (process-input RAW-INPUT))
(define WIDTH (+ 1 (max-posn posn-x INPUT)))
(define HEIGHT (+ 1 (max-posn posn-y INPUT)))

; --------------- PART 1 ---------------

; solve
(define (solve _)
  (num-dangerous (line-counts WIDTH HEIGHT INPUT)))

; num-dangerous : [List-of [List-of Nat]] -> Nat
; counts how many positions are at the intersection of multiple lines
(check-expect (num-dangerous (list '())) 0)
(check-expect (num-dangerous (list '(1 2 1) '(0 0 3))) 2)
(define (num-dangerous lolon)
  (length (filter (λ (n) (> 1 n))
                  (flatten lolon))))

; line-counts : Nat Nat [List-of Line] -> [List-of [List-of Nat]]
; finds the number of lines going through every point in a grid of
; the given width and height
(check-expect (line-counts 2 3 (list (make-line POSN1 POSN2)))
              (list '(1 0) '(1 0) '(1 0)))
(check-expect (line-counts 5 5 (list (make-line POSN1 POSN2)
                                     (make-line POSN2 POSN3)))
              (list '(1 0 0 0 0)
                    '(1 0 0 0 0)
                    '(1 0 0 0 0)
                    '(2 1 1 0 0)
                    '(0 0 0 0 0)))
(define (line-counts width height lol)
  (local [; in-lines : Posn [List-of Line] -> Nat
          ; finds the number of lines going through one point
          (define (in-lines p lines)
            (length (filter (λ (line) (in-line? p line)) lines)))]
    (build-list height
                (λ (y) (build-list width
                                   (λ (x) (in-lines (make-posn x y) lol)))))))

; in-line? : Posn Line -> Boolean
; is the point in the given line? (assumes horizontal or vertical lines)
(check-expect (in-line? (make-posn 0 0) LINE1) #t)
(check-expect (in-line? (make-posn 8 1) LINE3) #t)
(check-expect (in-line? (make-posn 9 1) LINE3) #t)
(check-expect (in-line? (make-posn 7 2) LINE2) #f)
(check-expect (in-line? (make-posn 0 4) LINE1) #f)
(check-expect (in-line? (make-posn 6 1) LINE3) #f)
(define (in-line? p l)
  (or (horizontal-line? (line-start l) (line-end l) p)
      (vertical-line? (line-start l) (line-end l) p)))

; horizontal-line? : Posn Posn Posn -> Boolean
; does the third point come between the first two horizontally?
(check-expect (horizontal-line? POSN3 POSN2 POSN3) #t)
(check-expect (horizontal-line? POSN3 POSN2 (make-posn 4 3)) #f)
(check-expect (horizontal-line? POSN3 POSN2 (make-posn 2 2)) #f)
(define (horizontal-line? start end mid)
  (and (= (posn-y start) (posn-y mid) (posn-y end))
       (or (<= (posn-x start) (posn-x mid) (posn-x end))
           (<= (posn-x end) (posn-x mid) (posn-x start)))))

; vertical-line? : Posn Posn Posn -> Boolean
; does the third point come between the first two vertically?
(check-expect (vertical-line? POSN1 POSN2 POSN1) #t)
(check-expect (vertical-line? POSN1 POSN2 (make-posn 0 2)) #t)
(check-expect (vertical-line? POSN1 POSN2 (make-posn 0 5)) #f)
(check-expect (vertical-line? POSN1 POSN2 (make-posn 1 2)) #f)
(define (vertical-line? start end mid)
  (and (= (posn-x start) (posn-x mid) (posn-x end))
       (or (<= (posn-y start) (posn-y mid) (posn-y end))
           (<= (posn-y end) (posn-y mid) (posn-y start)))))


