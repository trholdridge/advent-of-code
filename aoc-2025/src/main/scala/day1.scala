import cats.effect._
import java.io.File
import scala.io.Source

object Day1 extends IOApp {

  def part1(lines: Iterator[String]): Int = {
    lines.foldLeft[(Int, Int)]((0, 50)) { (soFar, line) => soFar match 
      case (count, position) =>
        val newPos = (((position + lineToInt(line)) % 100) + 100) % 100
        if (newPos == 0)
          (count + 1, newPos)
        else
          (count, newPos)
    }._1
  }

  def lineToInt(line: String): Int = {
    if (line.charAt(0) == 'R')
      line.substring(1).toInt
    else
      0 - line.substring(1).toInt
  }

  def part2(lines: Iterator[String]): Int = {
    lines.foldLeft[(Int, Int)]((0, 50)) { (soFar, line) => soFar match 
      case (count, position) =>
        val move = lineToInt(line)
        val newPos = (((position + move) % 100) + 100) % 100
        if (move > 0) {
          val crossed = if ((move % 100) + position >= 100) 1 else 0
          val extras = move / 100
          (count + crossed + extras, newPos)
        } else if (move == 0) {
          (count + (if (position == 0) 1 else 0), newPos)
        } else {
          val crossed = if ((move % 100) + position <= 0 && position > 0) 1 else 0
          val extras = Math.abs(move) / 100
          (count + crossed + extras, newPos)
        }
    }._1
  }

  override def run(args: List[String]): IO[ExitCode] =
    for {
      result <- IO(Source.fromResource("input1.txt")).bracket(src => IO(part2(src.getLines())))(src => IO(src.close()))
      _ <- IO.println(result)
    } yield ExitCode.Success
}