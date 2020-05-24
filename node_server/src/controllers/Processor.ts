import { Bot, Position } from '../interfaces/Data';
import { ReaderController } from './Reader';

export class ProcessorController {
  trackingBot(bot: Bot, generation: number) {
    const { fatherId, motherId } = bot;
    const reader = new ReaderController();

    const population = reader.getPopulationByGeneration(generation - 1);
    const mother = population.bots.find(cBot => cBot.id ===  motherId);
    const father = population.bots.find(cBot => cBot.id ===  fatherId);

    const initialPos = bot.dna[0];
    const initialMotherPos = mother.dna[0];
    const initialFatherPos = father.dna[0];

    let parent: Bot = null;
    if (this.equalsPosition(initialPos, initialMotherPos)) {
      parent = mother;
    } else if (this.equalsPosition(initialPos, initialFatherPos)) {
      parent = father;
    }

    return parent;
  }

  equalsPosition(p1: Position, p2: Position): boolean {
    return p1.i === p2.i && p1.j === p2.j;
  }
};
