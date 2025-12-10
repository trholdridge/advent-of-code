import cats.effect._
import java.io.File
import scala.io.Source

object Day3 extends IOApp {

  def part1(lines: Iterator[String]): Long = {
    lines.map { line =>
        val maxTens = line.take(line.length - 1).max
        val maxOnes = line.dropWhile(_ != maxTens).substring(1).max
        (maxTens.toString + maxOnes.toString).toInt
    }.sum
  }
  
  def part2(lines: Iterator[String]): Long = {
    lines.map(maxNum(_, 12).toLong).sum
  }

  def maxNum(s: String, toTake: Int): String = {
    if (toTake == 0)
        ""
    else
        val maxFirstChar = s.take(s.length - (toTake - 1)).max
        val rest = s.dropWhile(_ != maxFirstChar).substring(1)
        maxFirstChar.toString + maxNum(rest, toTake - 1)
  }

  override def run(args: List[String]): IO[ExitCode] =
    for {
      result <- IO(Source.fromResource("input3.txt")).bracket(src => IO(part2(src.getLines())))(src => IO(src.close()))
      _ <- IO.println(result)
    } yield ExitCode.Success
}