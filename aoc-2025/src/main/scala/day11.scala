import cats.effect._
import scala.io.Source

object Day11 extends IOApp {

  type Node = String
  type Path = List[String]

  def part1(lines: Iterator[String]): Long = {
    val g: Map[Node, List[Node]] = makeGraph(lines)
    paths("you", "out", g, Map()).length
  }

  def makeGraph(lines: Iterator[String]): Map[Node, List[Node]] = {
    lines.map { line =>
      val nodeAndEdges = line.split(":")
      (nodeAndEdges(0), nodeAndEdges(1).trim.split("\\s").toList)
    }.toMap
  }

  def paths(from: Node,
            to: Node,
            graph: Map[Node, List[Node]],
            savedPaths: Map[(Node, Node), List[Path]]): List[Path] = {
    savedPaths.getOrElse(
      (from, to),
      graph(from).flatMap(savedPaths(_, to).map(path => from :: path)))
  }

  def part2(lines: Iterator[String]): Long = {
    ???
  }

  override def run(args: List[String]): IO[ExitCode] =
    for {
      result <- IO(Source.fromResource("test.txt")).bracket(src =>
        IO(part1(src.getLines())))(src => IO(src.close()))
      _ <- IO.println(result)
    } yield ExitCode.Success
}
