import fs from 'fs';
import path from 'path';
import { Population, Bot } from '../interfaces/Data';

export class ReaderController {
  readInfo(): string[] {
    const directoryPath = path.join(__dirname, '../../../outputs');

    const files = fs.readdirSync(directoryPath);
    const regex = /gen_([0-9]+).json/;

    return files.sort((a, b) => {
      const numberA = parseInt(regex.exec(a)[1], 10);
      const numberB = parseInt(regex.exec(b)[1], 10);

      return numberB - numberA;
    });
  }

  getBestBot(generation: number): Bot {
    const currentPath = path.join(__dirname, '../../../outputs', `gen_${generation}.json`);
    const data = fs.readFileSync(currentPath, 'utf8');
    let json: Population = null;

    try {
      json = JSON.parse(data);
    } catch (err) {
      console.log(err);
    }

    if (!json) {
      return null;
    }

    const sortedBots = json.bots.sort((bot1: Bot, bot2: Bot) => {
      return bot2.dna.length - bot1.dna.length;
    });

    return sortedBots[0];
  }

  getPopulationByGeneration(generation: number): Population {
    const currentPath = path.join(__dirname, '../../../outputs', `gen_${generation}.json`);
    const data = fs.readFileSync(currentPath, 'utf8');
    try {
      return JSON.parse(data);

    } catch (err) {
      console.log('getPopulation', err);
      return null;
    }
  }
};