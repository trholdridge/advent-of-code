import cats.effect._
import java.io.File
import scala.io.Source

object Day7 extends IOApp {

  final case class Posn(x: Int, y: Int)

  final case class State(beamPosns: Set[Posn], numSplits: Long, done: Boolean)

  def part1(lines: Iterator[String]): Long = {
    val linesCopy = lines.toList

    val numRows = linesCopy.length
    val initialBeam: Set[Posn] = Set(Posn(linesCopy.head.indexOf('S'), 0))
    val splitters: List[Posn] = linesCopy.zipWithIndex.flatMap { case (row, rowIdx) =>
      row.zipWithIndex.collect { case ('^', colIdx) =>
        Posn(colIdx, rowIdx)
      }
    }

    var state: State = State(initialBeam, 0, false)
    while (!state.done) {
      state = step1(state, splitters, numRows)
    }

    state.numSplits
  }

  def step1(state: State, splitters: List[Posn], numRows: Int): State = {
    val oldBeamPosns = state.beamPosns

    val (newBeamPosns, newSplits) = state.beamPosns.map { case Posn(x, y) =>
      if (y >= numRows - 1)
        (Set(Posn(x, y)), 0)
      else if (splitters.contains(Posn(x, y + 1)))
        (Set(Posn(x - 1, y + 1), Posn(x + 1, y + 1)), 1)
      else
        (Set(Posn(x, y + 1)), 0)
    }.reduce { case ((beams1, splits1), (beams2, splits2)) =>
      (beams1 ++ beams2, splits1 + splits2)
    }

    // numSplits will represent the number of times the beam has split
    State(newBeamPosns, state.numSplits + newSplits, newBeamPosns == oldBeamPosns)
  }

  def part2(lines: Iterator[String]): Long = {
    val linesCopy = lines.toList

    val numRows = linesCopy.length
    val initialBeam: Set[Posn] = Set(Posn(linesCopy.head.indexOf('S'), 0))
    val splitters: List[Posn] = linesCopy.zipWithIndex.flatMap { case (row, rowIdx) =>
      row.zipWithIndex.collect { case ('^', colIdx) =>
        Posn(colIdx, rowIdx)
      }
    }

    var state: State = State(initialBeam, 0, false)
    while (!state.done) {
      state = step2(state, splitters, numRows)
    }

    state.numSplits
  }

  def step2(state: State, splitters: List[Posn], numRows: Int): State = {
    val oldBeamPosns = state.beamPosns

    val (newBeamPosns, newSplits) = state.beamPosns.map { case Posn(x, y) =>
      if (y >= numRows - 1)
        (Set(Posn(x, y)), 0)
      else if (splitters.contains(Posn(x, y + 1)))
        (Set(Posn(x - 1, y + 1), Posn(x + 1, y + 1)), 1)
      else
        (Set(Posn(x, y + 1)), 0)
    }.reduce { case ((beams1, splits1), (beams2, splits2)) =>
      (beams1 ++ beams2, splits1 + splits2)
    }

    // numSplits will represent the number of timelines
    State(newBeamPosns, state.numSplits + math.pow(2, newSplits).toLong, newBeamPosns == oldBeamPosns)
  }

  override def run(args: List[String]): IO[ExitCode] =
    for {
      result <- IO(Source.fromResource("test.txt")).bracket(src => IO(part2(src.getLines())))(src => IO(src.close()))
      _ <- IO.println(result)
    } yield ExitCode.Success
}