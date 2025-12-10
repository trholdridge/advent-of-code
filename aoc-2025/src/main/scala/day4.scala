import cats.effect._
import java.io.File
import scala.io.Source

object Day4 extends IOApp {

  def part1(lines: Iterator[String]): Long = {
    val grid = lines.toArray.map(_.toCharArray.map(_ == '@'))
    (0 until grid(0).length).flatMap { x =>
      (0 until grid.length).map { y =>
        (x, y)
      }
    }.count(coord => grid(coord._2)(coord._1) && lessThanFour(coord, grid))
  }

  def lessThanFour(coord: (Int, Int), grid: Array[Array[Boolean]]): Boolean = {
    (coord._1 - 1 to coord._1 + 1).flatMap { x =>
        (coord._2 - 1 to coord._2 + 1).map { y =>
            x >= 0 
              && y >= 0 
              && x < grid(0).length
              && y < grid.length
              && (x != coord._1 || y != coord._2)
              && grid(y)(x)
        }
    }.count(identity) < 4
  }

  def part2(lines: Iterator[String]): Long = {
    val grid = lines.toArray.map(_.toCharArray.map(_ == '@'))
    val initial = countPaper(grid)

    val finalGrid = removeStuff(grid)

    initial - countPaper(finalGrid)
  }

  def removeStuff(grid: Array[Array[Boolean]]): Array[Array[Boolean]] = {
    val removed = removePaper(grid)
    
    if (countPaper(grid) == countPaper(removed))
      removed
    else
      removeStuff(removed)
  }

  def removePaper(grid: Array[Array[Boolean]]): Array[Array[Boolean]] = {
    (0 until grid(0).length).toArray.map { x =>
      (0 until grid.length).toArray.map { y =>
        grid(y)(x) && !lessThanFour((x, y), grid)
      }
    }
  }

  def countPaper(grid: Array[Array[Boolean]]): Long = {
    grid.map(_.count(identity)).sum
  }

  override def run(args: List[String]): IO[ExitCode] =
    for {
      result <- IO(Source.fromResource("input4.txt")).bracket(src => IO(part2(src.getLines())))(src => IO(src.close()))
      _ <- IO.println(result)
    } yield ExitCode.Success
}