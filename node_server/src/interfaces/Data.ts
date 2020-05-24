export type Position = {
  i: number;
  j: number;
};

export type Bot = {
  id: number;
  dna: Position[];
  fatherId: number;
  motherId: number;
};

export type Population = {
  gen: number;
  bots: Bot[];
};